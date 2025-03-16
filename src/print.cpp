#include "../h/print.hpp"
#include "../lib/hw.h"

#include "../lib/console.h"
uint64 myLockPrint = 0;

void myPrintString(char const *string)
{
    while (*string != '\0')
    {
        __putc(*string);
        string++;
    }
}

char myDigits[] = "0123456789ABCDEF";

void myPrintInt(int xx, int base, int sgn)
{
    char buf[16];
    int i, neg;
    uint x;

    neg = 0;
    if(sgn && xx < 0){
        neg = 1;
        x = -xx;
    } else {
        x = xx;
    }

    i = 0;
    do{
        buf[i++] = myDigits[x % base];
    }while((x /= base) != 0);
    if(neg)
        buf[i++] = '-';

    while(--i >= 0)
        __putc(buf[i]);

}