#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QThread>
#include <list>
#include <QMessageBox>
#include <math.h>
#include "qcustomplot.h"
#include "Rf.h"
#include "RFV4/RfV4.h"
#include "Instrument.h"
#include "Logger.h"

using namespace std;

class QMyThread : public QThread
{
	Q_OBJECT
public:
	QMyThread(QWidget *parent);
	~QMyThread();
	virtual void run();
	virtual void cancel();
	virtual void setFreqs(list<double> freqs);
    virtual void setCalFile(CalFileV4 *calFile);
	virtual void setConnected(int connected);
	virtual void setPort(int port);
	virtual const double *temp();
	int result();
    void  shiftTemp(const double *temp, double *shift);
public:
	const QWidget *parent() const;
protected:
	int   message(const QString &title, const QString &text);
	int   question(const QString &title, const QString &text);
	void  tick();
	void  setTicks(size_t ticks);
	FILE *openLog(const char *fileName, ...);
	int   writeLog(const char *format, ...);
	void  closeLog();
public:
	enum Results {
		PASS,
		FAIL,
		FINISH,
	};
	static const QString results[];
private:
	QWidget       *m_parent;
	int            m_ticks;
	int            m_tick;
	QWaitCondition m_wait;
	QMutex         m_mutex;
	int            m_answer;
	FILE          *m_file;
	int            m_connected;
	int            m_running;
    double         m_temp[Rf::SENSOR_MAX];
	int            m_port;
protected:
	list<double> m_freqs;
    CalFileV4     *m_calFile;
	int          m_result;
protected:
	int connected()       { return m_connected; }
	int running()         { return m_running; }
	list<double> &freqs() { return m_freqs; }
    CalFileV4 *calFile()    { return m_calFile; }
	int port()            { return m_port; }
private slots:
	void askingQuestion(const QString &title, const QString &text, int *answer);
	void showingMessagebox(const QString &title, const QString &text);
signals:
	void askQuestion(const QString &title, const QString &text, int *answer);
	void showMessageBox(const QString &title, const QString &text);
signals:
	void done(int);
	void log(QString message, int type = logtool::log_msg);
	void error(QString message);
	void addPlot(QString label, double x, double y);
};

#endif // QMYTHREAD_H
