#ifndef _REG_DEFINE_H_
#define _REG_DEFINE_H_

#include "Log.h"

#define REG_DEF_S(reg_addr)      \
	union reg_##reg_addr {       \
		uint32_t u32;            \
		struct reg_t {

#define REG_DEF_E                \
	} __attribute__((packed)) r; \
};

#define REG_DECLARE(reg_addr) union reg_##reg_addr r##reg_addr = { 0 };
#define REG(reg_addr) r##reg_addr.r
#define REGU(reg_addr) r##reg_addr
#define K7W(reg_addr) \
	do { \
        if (m_k7.out32(1, (reg_addr << 2), r##reg_addr.u32)) \
			return EREG; \
		Log.printf(LM_reg, "--> 0x%04x 0x%08x\n", reg_addr, r##reg_addr.u32); \
	} while (0);
#define K7R(reg_addr) \
	do { \
		if (m_k7.in32(1, (reg_addr << 2), &r##reg_addr.u32)) \
			return EREG; \
		Log.printf(LM_reg, "<-- 0x%04x 0x%08x\n", reg_addr, r##reg_addr.u32); \
	} while (0);

#define K7IdleWait(reg_addr, reg_member, idle_flag)                                            \
	do {                                                                                       \
		int r##reg_addr_busy_cnt = 0;                                                          \
		K7R(reg_addr);                                                                         \
		do {                                                                                   \
			K7R(reg_addr);                                                                     \
			if (++r##reg_addr_busy_cnt > 1000) {                                               \
				Log.printf(LM_reg, "[ %s : %d ] retry 1000 times\n", __FILE__, __LINE__);      \
				r##reg_addr_busy_cnt = 0;                                                      \
			}                                                                                  \
		} while (r##reg_addr.r.reg_member != idle_flag);                                       \
	} while (0);

#define IdleWait(reg_addr) K7IdleWait(reg_addr, busy, 0)

#define SPIOP(reg_addr, reg_member)    \
    do {                              \
        r##reg_addr.r.reg_member = 0; \
        K7W(reg_addr);                \
        usleep(2);                    \
        r##reg_addr.r.reg_member = 1; \
        K7W(reg_addr);                \
        usleep(2);                    \
        r##reg_addr.r.reg_member = 0; \
        K7W(reg_addr);                \
    } while (0);
#define SPI_OP(reg_addr) SPIOP(reg_addr, op)


#define CLEAR(reg_addr) r##reg_addr.u32 = 0;


REG_DEF_S(0x0000)
    unsigned adr   : 10;
    unsigned data  : 10;
    unsigned rsv   : 10;
    unsigned busy  : 1;
    unsigned op    : 1;
REG_DEF_E

struct struct_1 {
    unsigned li       : 1;
    unsigned hong     : 1;
    unsigned chao     : 4;
    unsigned hchao    : 1;
    unsigned lhc      : 1;
    unsigned lhchao   : 3;
    unsigned rsv      : 5;
} __attribute__((packed));


struct struct_2 {
    unsigned rsv      : 4;
    unsigned chao1    : 6;
    unsigned chao2    : 6;

} __attribute__((packed));

REG_DEF_S(0x0001)
    union {
        struct struct_1 r1;
        struct struct_2 r2;

    } u;
    unsigned adr : 8;
REG_DEF_E


#endif // REG_DEFINE_H

