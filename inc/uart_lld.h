#ifndef INC_UART_LLD_H_
#define INC_UART_LLD_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

void dbgprintf( const char* format, ... );
void debug_stream_init( void );
void uart_init(void);
void digit_output(uint8_t buf);

#endif
