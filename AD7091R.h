#ifndef AD7091R_H
#define AD7091R_H

#include <stdint.h>

#define OUT_OF_RANGE_PIN_NUMBER 99
#define ERROR_VALUE -999
#define TRUE 1
#define FALSE 0

typedef struct AD7091R_t {
  uint8_t convst_pin;
  uint8_t cs_pin;
  uint8_t clk_pin;
  uint8_t data_pin;
} AD7091R;




int AD7091R_alloc(AD7091R **pp_instance);
int AD7091R_dealloc(AD7091R *p_instance);

int AD7091R_pins(AD7091R *p_instance, 
	         uint8_t n_convst_pin,
                 uint8_t n_cs_pin,
                 uint8_t n_clk_pin,
                 uint8_t n_data_pin);

int AD7091R_convst_pin(AD7091R *p_instance,
	           uint8_t n_convst_pin);
int AD7091R_cs_pin(AD7091R *p_instance,
	       uint8_t n_cs_pin);
int AD7091R_clk_pin(AD7091R *p_instance,
                uint8_t n_clk_pin);
int AD7091R_data_pin(AD7091R *p_instance,
                 uint8_t n_data_pin);

int AD7091R_begin(AD7091R *p_instance);
int AD7091R_reset(AD7091R *p_instance);
int AD7091R_data(AD7091R *p_instance);


#endif
