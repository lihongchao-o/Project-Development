#ifndef CD_TxTable_H
#define CD_TxTable_H

#include <QDialog>
#include "qcustomplot.h"
#include "Rf.h"
#include "RFV4/RfV4.h"
#include "CT_TxTable.h"

namespace Ui {
class CD_TxTable;
}

class CD_TxTable : public QDialog
{
	Q_OBJECT

public:
	explicit CD_TxTable(QWidget *parent = 0);
	~CD_TxTable();
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
	Ui::CD_TxTable *ui;
    CalFileV4 *m_calFile;
	CalThread_TxTable *m_worker;
};

#endif // CD_TxTable_H
