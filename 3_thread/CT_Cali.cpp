#include "CT_TxTable.h"
#include <QMessageBox>
#include <math.h>



CalThread_TxTable::CalThread_TxTable(QWidget *parent)
	: QMyThread(parent)
{

}

CalThread_TxTable::~CalThread_TxTable()
{
}

void CalThread_TxTable::run() {
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

bool CalThread_TxTable::cal(double freqMHz) {
    double base;

    writeLog("\n\n/****************************************************************************/\n");

    base = measure(freqMHz);
    writeLog("开始校准 %f MHz, 基准 = %d dBm\n"
             , freqMHz, base);



	return true;
}

double CalThread_TxTable::measure(double freqMHz) {

    double pm;

    PM_GetPwr(freqMHz, pm);//test

    return pm;

}

