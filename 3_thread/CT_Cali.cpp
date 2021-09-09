#include "CT_Cali.h"
#include <QMessageBox>
#include <math.h>



CalThread_Cali::CalThread_Cali(QWidget *parent)
	: QMyThread(parent)
{

}

CalThread_Cali::~CalThread_Cali()
{
}

void CalThread_Cali::run() {
#ifdef MODULE_DEBUG
	return 0;
#endif

    openLog("Cali1");

	list<double>::const_iterator it;
	int i;


	for (i = 0, it = m_freqs.begin(); it != m_freqs.end(); it++, i++) {
		if (!running()) {
            emit error("取消Cali1");
			closeLog();
			return;
		}
        if (!cal(*it)) {
			closeLog();
			return;
		}
	}

	closeLog();
	emit done(result());
}

bool CalThread_Cali::cal(double freqMHz) {
    double base;

    writeLog("\n\n/****************************************************************************/\n");

    base = measure(freqMHz);
    writeLog("开始校准 %f MHz, 基准 = %d dBm\n"
             , freqMHz, base);



	return true;
}

double CalThread_Cali::measure(double freqMHz) {

    double pm;

    PM_GetPwr(freqMHz, pm);//test

    return pm;

}

