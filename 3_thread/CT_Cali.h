/*
 *
 *  CalThread_TxTable.h: interface for the CCalThread_TxTable class.
 *
 */

#ifndef	CAL_THREAD_TXTABLE_H
#define CAL_THREAD_TXTABLE_H

#include <stdio.h>
#include "qmythread.h"

class CalThread_TxTable : public QMyThread
{
	Q_OBJECT
public:
	CalThread_TxTable(QWidget *parent);
	virtual ~CalThread_TxTable();
	void run();
private:
    bool   cal(double freqMHz);
	double measure(double freqMHz);
};

#endif
