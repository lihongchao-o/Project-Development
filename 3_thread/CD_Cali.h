#ifndef CD_Cali_H
#define CD_Cali_H

#include <QDialog>
#include "qcustomplot.h"
#include "CT_Cali.h"

namespace Ui {
class CD_Cali;
}

class CD_Cali : public QDialog
{
	Q_OBJECT

public:
	explicit CD_Cali(QWidget *parent = 0);
	~CD_Cali();
	static const QString m_Title;

private slots:
	void on_startPushButton_clicked();

private slots:
	void on_thread_done(int result);
	void on_thread_error(QString s);
	void on_thread_addPlot(QString s, double x, double y);
	void on_plot_plottableDoubleClick(QCPAbstractPlottable *plot, QMouseEvent *e);
private:
	QMap<QString, QCPGraph *> m_graphs;
	void success();

private:
	Ui::CD_Cali *ui;
    CalFileV4 *m_calFile;
	CalThread_Cali *m_worker;
};

#endif // CD_Cali_H
