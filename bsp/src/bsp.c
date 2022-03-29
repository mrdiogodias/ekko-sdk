#include <bsp.h>

/* Todo: Find out why the first initialized global variable is set to zero if ThreadX is used.
         Probably something related to the port, which is overlaping the first variable? */
uint32_t *dummy_var = (uint32_t*) 0xdeadbeef;

static void delay_loop_ibex(unsigned long loops) {
    int out; /* only to notify compiler of modifications to |loops| */
    asm volatile(
        "1: nop             \n" // 1 cycle
        "   nop             \n" // 1 cycle
        "   nop             \n" // 1 cycle
        "   nop             \n" // 1 cycle
        "   addi %1, %1, -1 \n" // 1 cycle
        "   bnez %1, 1b     \n" // 3 cycles
        : "=&r"(out)
        : "0"(loops));
}

static void usleep_ibex(unsigned long usec) {
    unsigned long freq = SYS_CLK_FREQ / 1000000;
    unsigned long usec_cycles = freq * usec / 8;

    delay_loop_ibex(usec_cycles);
}

void sleep_us(unsigned long us) {
    usleep_ibex(us);
}

void sleep_ms(unsigned long ms) {
    usleep_ibex(ms * 1000);
}

void *my_memset(void *s, int c, unsigned int len) {
    unsigned char *p = s;

    while (len--) {
        *p++ = (unsigned char)c;
    }

    return s;
}