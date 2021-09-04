#include <math.h>
#include "Log.h"


void SetLogPrinter(void (*printer)(char *)) {
	Log.setPrinter(printer);
}

void RF_SetLogModules(uint32_t lms) {
    static const LMs cal[] = { LM_cal1, LM_cal2};
    static const LMs test[] = { LM_test1, LM_test2};
    static const LMs base[] = { LM_init, LM_drv, LM_reg, LM_rdma, LM_tdma, LM_err };

    size_t size = sizeof(cal) / sizeof(cal[0]);
    if (lms & drvLM_cal) {
		for (size_t i = 0; i < size; i++)
            Log.enable(cal[i]);
	} else {
		for (size_t i = 0; i < size; i++)
            Log.disable(cal[i]);
	}

    size = sizeof(test) / sizeof(test[0]);
    if (lms & drvLM_test) {
		for (size_t i = 0; i < size; i++)
            Log.enable(test[i]);
	} else {
		for (size_t i = 0; i < size; i++)
            Log.disable(test[i]);
	}

    size = sizeof(base) / sizeof(base[0]);
    if (lms & drvLM_base) {
		for (size_t i = 0; i < size; i++)
            Log.enable(base[i]);
	} else {
		size_t size = sizeof(drv) / sizeof(drv[0]);
		for (size_t i = 0; i < size; i++)
            Log.disable(base[i]);
	}
}

int Test(int enable) {

    Log.printf(LM_test1, "EnableTemp %d\n", enable);


    return 0;
}


