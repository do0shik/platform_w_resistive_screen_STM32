#include <test_adc.h>

ADCConversionGroup adcconf1 = {

   .circular = FALSE,
   .num_channels = 1,
   .end_cb = NULL,
   .error_cb = NULL,
   .cr1 = 0,
   .cr2 = 0,
   .smpr1 = 0,
   .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLE_7P5),
   .sqr1 = 0,
   .sqr2 = 0,
   .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)
};

void adc_init(void){
 adcStart(&ADCD1, NULL);
 palSetLineMode(PAL_LINE(GPIOA, 0), PAL_MODE_INPUT_ANALOG);
}

void adc_read (uint16_t *adcbuf) {
 adcConvert(&ADCD1, &adcconf1, adcbuf, 1);
}


