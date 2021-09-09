#include "CD_Cali.h"
#include "CT_Cali.h"
#include <QMessageBox>

const QString CD_Cali::m_Title = QString("Cal_1");

CD_Cali::CD_Cali(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::CD_Cali)
	, m_worker(NULL)
{
	ui->setupUi(this);
	setWindowTitle(m_Title);

    ui->lineFreqEdit->setText("112~6000:50;");
	ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	ui->plot->legend->setVisible(true);
	ui->plot->legend->setSelectableParts(QCPLegend::spLegendBox);
}

CD_Cali::~CD_Cali()
{
	delete ui;
}

void CD_Cali::on_startPushButton_clicked()
{
	if (m_worker) {
		ui->startPushButton->setEnabled(false);
		m_worker->cancel();
		while (!m_worker->isFinished());
		ui->startPushButton->setEnabled(true);
		ui->startPushButton->setText("开始");
		m_worker = NULL;
	} else {
		list<double> freqs;
		if (ui->lineFreqEdit->getFreqs(freqs) < 0)
			return;
		cfg.tx_tab_freqs = ui->lineFreqEdit->text();
        m_calFile = RFV4.calFile();

		m_graphs.clear();
		ui->plot->clearGraphs();

		m_worker = new CalThread_Cali(this);
		m_worker->setFreqs(freqs);
        m_worker->setCalFile(RFV4.calFile());

		connect(m_worker, SIGNAL(done(int)), this, SLOT(on_thread_done(int)));
		connect(m_worker, SIGNAL(error(QString)), this, SLOT(on_thread_error(QString)));
		connect(m_worker, SIGNAL(addPlot(QString,double,double)), this, SLOT(on_thread_addPlot(QString,double,double)));

		m_worker->start();
		ui->startPushButton->setText("取消");
	}
}

void CD_Cali::success() {
	m_calFile->save();
}

void CD_Cali::on_thread_done(int result) {
	success();
	ui->startPushButton->setText("开始");

	if (result == QMyThread::FAIL)
		QMessageBox::critical(this, m_Title, QMyThread::results[result]);
	else
		QMessageBox::information(this, m_Title, QMyThread::results[result]);
}

void CD_Cali::on_thread_error(QString message) {
	QMessageBox::critical(this, m_Title, message);
	ui->startPushButton->setText("开始");
}

void CD_Cali::on_thread_addPlot(QString s, double x, double y) {
	if (m_graphs.size() < 100) {
		if (m_graphs.find(s) == m_graphs.end()) {
			QPen pen;
			QCPGraph *graph = ui->plot->addGraph();
			int i = m_graphs.size();

			pen.setColor(QColor(qSin(i * 0.3) * 100 + 100
							   , qSin(i * 0.6 + 0.7) * 100 + 100
							   , qSin(i * 0.4 + 0.6) * 100 + 100));

			graph->setName(s);
			graph->setPen(pen);
			graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
			m_graphs[s] = graph;
		}
		m_graphs[s]->addData(x, y);
		ui->plot->rescaleAxes(true);
		ui->plot->replot();
	}
}

void CD_Cali::on_plot_plottableDoubleClick(QCPAbstractPlottable *plot, QMouseEvent *e) {
	(void)e;
	QMessageBox::information(this, m_Title, plot->name());
}
