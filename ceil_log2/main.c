#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int ceil_ilog2(uint32_t x)
{
    uint32_t r, shift;

    x -= (!!x);
    r = (x > 0xFFFF) << 4;                                                                                                                                    
    x >>= r;
    shift = (x > 0xFF) << 3;
    x >>= shift;
    r |= shift;
    shift = (x > 0xF) << 2;
    x >>= shift;
    r |= shift;
    shift = (x > 0x3) << 1;
    x >>= shift;
    x = !(r | shift | x > 0) ? 0 : (r | shift | x > 1)+1;
    return x;       
}
int main(int argc, char *argv[])
{
    uint32_t x = atoi(argv[1]);
    printf("%d\n",ceil_ilog2(x));

    return 0;
}

