#ifndef _LOG_H_
#define _LOG_H_

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include <string.h>
#include <stdint.h>

#define Log logger::instance()

enum LMs {
    LM_cal1  = 0x01,
    LM_cal2,
    LM_test1,
    LM_test2,
	LM_init,
	LM_drv,
	LM_reg,
	LM_rdma,
	LM_tdma,
	LM_err,
};
/* increase according to actual situation*/
const char mod_names[][32] = {
	"",
    "[CAL1]",
    "[CAL2]",
    "[TEST1]",
    "[TEST2]",
	"[INIT]",
	"[DRV]",
	"[REG]",
	"[RX DMA]",
	"[TX DMA]",
	"[ERROR]",
};

class logger {
private:
	logger();
	logger(logger &);
	logger operator &= (logger);
public:
	static logger &instance();
	void printf(LMs LM, const char *format, ...);
public:
	typedef void (*PRINTER)(char *);
	void enable(LMs LM);
	void disable(LMs LM);
	void setPrinter(PRINTER printer);
	PRINTER printer();
	uint64_t flag();
	void setFlag(uint64_t flag);
private:
	const char *get_timestamp();
	uint64_t m_flag;
	void (*m_printer)(char *);
};

enum drvLMs {
    drvLM_cal  = 1,
    drvLM_test  = 2,
    drvLM_base  = 4,
};

/* declared in another file*/
extern void SetLogPrinter(void (*)(char *));

#endif
