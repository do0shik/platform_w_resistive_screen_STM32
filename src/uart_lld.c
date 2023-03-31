#include <uart_lld.h>


static SerialDriver *uart2 = &SD2;
static BaseSequentialStream *debug_stream = NULL;

SerialConfig uart2_conf = {
  .speed = 115200,
  .cr1 = 0,
  .cr2 = 0,
  .cr3 = 0
};

void debug_stream_init( void )
{
  uart_init();
// �������������� ��������� �� �����
    debug_stream = (BaseSequentialStream *)uart2;
}

// ������� �������� ������ � ��������
void dbgprintf( const char* format, ... )
{
// ���������, ��� debug_stream_init() ��������
    if ( !debug_stream )
    return;

// ���������� � chvprintf() ������ � ��� ����
    va_list ap;
    va_start(ap, format);
    chvprintf(debug_stream, format, ap);
    va_end(ap);
}

void uart_init(void)
{
    sdStart(uart2, &uart2_conf);
    palSetLineMode( PAL_LINE( GPIOA, 2), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode( PAL_LINE( GPIOA, 3), PAL_MODE_INPUT_PULLUP);
}

void digit_output(uint8_t buf)
{
    sdWrite(uart2, &buf, 1);
}

