#include "qmythread.h"


const QString QMyThread::results[] = {
	"测试通过", "测试失败", "测试完成"
};

QMyThread::QMyThread(QWidget *parent)
	: m_parent(parent)
	, m_file(NULL)
	, m_connected(0)
	, m_running(1)
	, m_port(0)
	, m_calFile(NULL)
	, m_result(FINISH)
{
	connect(this, SIGNAL(askQuestion(QString,QString,int*)), this, SLOT(askingQuestion(QString,QString,int*)));
	connect(this, SIGNAL(showMessageBox(QString,QString)), this, SLOT(showingMessagebox(QString,QString)));
}

QMyThread::~QMyThread()
{

}


void QMyThread::run() {

}

void QMyThread::cancel() {
	m_running = 0;
}

void QMyThread::setFreqs(list<double> freqs) {
	m_freqs = freqs;
	m_freqs.sort();
}

void QMyThread::setCalFile(CalFileV4 *calFile) {
	m_calFile = calFile;
}

void QMyThread::setConnected(int connected) {
	m_connected = connected;
}

void QMyThread::setPort(int port) {
	m_port = port;
}

const double *QMyThread::temp() {
    RFV4.allTS(m_temp);
	return m_temp;
}
void  QMyThread::shiftTemp(const double *temp, double *shift)
{
    double averageTemp = 0;
    double averageTemps[Rf::TS_MAX];
    for(int i = 0;i<Rf::SENSOR_MAX;i++)
    {
        averageTemp += temp[i];
    }
    averageTemp = averageTemp /Rf::SENSOR_MAX;
    for(int i = 0;i<Rf::TS_MAX;i++)
    {
        averageTemps[i] = averageTemp;
    }
    memcpy(shift,averageTemps,sizeof(double) * Rf::TS_MAX);
}
int QMyThread::result() {
	return m_result;
}

const QWidget *QMyThread::parent() const {
	return m_parent;
}

int QMyThread::message(const QString &title, const QString &text) {
	QMutexLocker locker(&m_mutex);
	emit showMessageBox(title, text);
	m_wait.wait(&m_mutex);
	return 0;
}

void QMyThread::tick() {

}

void QMyThread::setTicks(size_t ticks) {
	m_ticks = ticks;
}

void QMyThread::askingQuestion(const QString &title, const QString &text, int *answer) {
	QMutexLocker locker(&m_mutex);
	*answer = QMessageBox::question(m_parent, title, text);
	m_wait.wakeOne();
}

int QMyThread::question(const QString &title, const QString &text) {
	int answer;
	QMutexLocker locker(&m_mutex);
	emit askQuestion(title, text, &answer);
	m_wait.wait(&m_mutex);
	return (answer == QMessageBox::Yes);
}

void QMyThread::showingMessagebox(const QString &title, const QString &text) {
	QMutexLocker locker(&m_mutex);
	QMessageBox::information(m_parent, title, text);
	m_wait.wakeOne();
}

FILE *QMyThread::openLog(const char *fileName, ...) {
	va_list ap;
	char filePath[512];
	va_start(ap, fileName);
	vsprintf(filePath, fileName, ap);
	va_end(ap);
	sprintf(&filePath[strlen(filePath)], "_%s.log", QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss").toUtf8().constData());
	if (m_file)
		closeLog();
	m_file = fopen(filePath, "w");
	return m_file;
}

int QMyThread::writeLog(const char *format, ...) {
	if (m_file == NULL)
		return -1;
	va_list ap;
	char buf[2048];
	bzero(buf, 2048);
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);

	fprintf(m_file, "%s", buf);
	qDebug(buf);
	return 0;
}

void QMyThread::closeLog() {
	fclose(m_file);
	m_file = NULL;
}
