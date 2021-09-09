/*
 *
 *  CalThread_Cali.h: interface for the CCalThread_Cali class.
 *
 */

#ifndef	CAL_THREAD_Cali_H
#define CAL_THREAD_Cali_H

#include <stdio.h>
#include "qmythread.h"

class CalThread_Cali : public QMyThread
{
	Q_OBJECT
public:
	CalThread_Cali(QWidget *parent);
	virtual ~CalThread_Cali();
	void run();
private:
    bool   cal(double freqMHz);
	double measure(double freqMHz);
};

#endif
