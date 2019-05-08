#ifndef AD7091R_H
#define AD7091R_H

#include <stdint.h>

#define OUT_OF_RANGE_PIN_NUMBER 99

typedef struct AD7091R_t {
  uint8_t convst_pin;
  uint8_t cs_pin;
  uint8_t clk_pin;
  uint8_t data_pin;
} AD7091R;

int alloc_AD7091R(AD7091R **pp_instance);
int set_pins(AD7091R *p_instance, 
	     uint8_t n_convst_pin,
             uint8_t n_cs_pin,
             uint8_t n_clk_pin,
             uint8_t n_data_pin);

int set_convst(AD7091R *p_instance,
	       uint8_t n_convst_pin);
int set_cs(AD7091R *p_instance,
	   uint8_t n_cs_pin);
int set_clk(AD7091R *p_instance,
            uint8_t n_clk_pin);
int set_data(AD7091R *p_instance,
             uint8_t n_data_pin);

int begin(AD7091R *p_instance);
void reset(AD7091R *p_instance);
uint16_t data(AD7091R *p_instance);


#endif
