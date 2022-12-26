#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdarg.h>

void eapp_print(const char* s, ...);

#define PRINT_ERR(fmt, args...)      eapp_print(fmt, ##args)
#define PRINT_INFO(fmt, args...)     eapp_print(fmt, ##args)
#define PRINTK(fmt, args...)         eapp_print(fmt, ##args)
#endif