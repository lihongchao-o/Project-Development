#include <iostream>
#include "RegisterDefine.h"

using namespace std;

int main()
{
    uint32_t u32 = 0;
    REG_DECLARE(0x0000);//declare register
    REG_DECLARE(0x0001);



    REG(0x0000).adr = 0x100000;//lvalue
    REG(0x0000).data = 123;
    K7W(0x0000);//write

    SPI_OP(0x0000);//spi

    K7R(0x0000);//read

    if(REG(0x0000).data == 123)
        cout << "read is right...\n";


    K7IdleWait(0x0000, busy, 0);//IdleWait(0x1037);

    u32 = REGU(0x0000).u32;//rvalue


    IdleWait(0x0001);

    REG(0x0001).adr = 1;
    REG(0x0001).u.r2.chao1  = 1;
    REG(0x0001).u.r2.chao2  = 2;

    SPI_OP(0x0001);


    return 0;
}
