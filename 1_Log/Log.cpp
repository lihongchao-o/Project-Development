#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include <string.h>
#include <stdint.h>
#include "Log.h"

static void std_printer(char *buf) {
	fprintf(stdout, "%s", buf);
	fflush(stdout);
}


logger::logger()
	: m_flag(0)
	, m_printer(std_printer) {
    disable(LM_cal1);
    disable(LM_cal2);
    disable(LM_test1);
    disable(LM_test2);
    disable(LM_init);
    disable(LM_drv);
    disable(LM_reg);
    disable(LM_rdma);
    disable(LM_tdma);
    disable(LM_err);

}

logger::logger(logger &) {
}

logger logger::operator &= (logger) {
	return *this;
}

logger &logger::instance() {
	static logger s_logger;
	return s_logger;
}

void logger::printf(LMs LM, const char *format, ...) {
	if ((m_flag & (1 << LM)) && m_printer) {
		char buf[4096];
		bzero(buf, 4096);
		sprintf(buf, "%s %10s ", get_timestamp(), mod_names[LM]);
		va_list ap;
		va_start(ap, format);
		vsprintf(&buf[strlen(buf)], format, ap);
		va_end(ap);

		m_printer(buf);
	}
}

void logger::setPrinter(PRINTER printer) {
	m_printer = printer;
}

logger::PRINTER logger::printer() {
	return m_printer;
}

void logger::enable(LMs LM) {
	m_flag |= (1 << LM);
}

void logger::disable(LMs LM) {
	m_flag &= ~(1 << LM);
}

const char *logger::get_timestamp() {
	static char bufp[2048];
	struct timeval tv;
	struct tm *p;

	gettimeofday(&tv, NULL);
	p = localtime(&tv.tv_sec);
	sprintf(bufp, "%4d-%2d-%2d %d:%2d:%2d.%6ld", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);
	return bufp;
}

uint64_t logger::flag() {
	return m_flag;
}

void logger::setFlag(uint64_t flag) {
	m_flag = flag;
}
