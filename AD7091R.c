#include "AD7091R.h"
#include <stdint.h>
#include <bcm2835.h>

int AD7091R_alloc(AD7091R **pp_instance) {
  AD7091R *instance;

  instance = malloc(sizeof(AD7091R));
  
  if(instance != 0) {
    instance->convst_pin = OUT_OF_RANGE_PIN_NUMBER;
    instance->cs_pin = OUT_OF_RANGE_PIN_NUMBER;
    instance->clk_pin = OUT_OF_RANGE_PIN_NUMBER;
    instance->data_pin = OUT_OF_RANGE_PIN_NUMBER;

    return TRUE;
  }
  else {
    return FALSE;
  }	
}

int AD7091R_dealloc(AD7091R *p_instance) {

  if(p_instance != 0) {
    free(p_intance);

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_pins(AD7091R *p_instance, 
	         uint8_t n_convst_pin,
                 uint8_t n_cs_pin,
                 uint8_t n_clk_pin,
                 uint8_t n_data_pin) {

  if(p_instance != 0) {
    p_instance->convst_pin = n_convst_pin;
    p_instance->cs_pin = n_cs_pin;
    p_instance->clk_pin = n_clk_pin;
    p_instance->data_pin = n_data_pin;

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_convst(AD7091R *p_instance,
	           uint8_t n_convst_pin) {

  if(p_instance != 0) {

    p_instance->convst_pin = n_convst_pin;

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_cs(AD7091R *p_instance,
	       uint8_t n_cs_pin) {

  if(p_instance != 0) {

    p_instance->cs_pin = n_cs_pin;

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_clk(AD7091R *p_instance,
                uint8_t n_clk_pin) {

  if(p_instance != 0) {

    p_instance->clk_pin = n_clk_pin;

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_data(AD7091R *p_instance,
                 uint8_t n_data_pin) {

  if(p_instance != 0) {

    p_instance->data_pin = n_data_pin;

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_begin(AD7091R *p_instance) {

  if(p_instance != 0) {

    if(p_instance->convst_pin == OUT_OF_RANGE_PIN_NUMBER ||
       p_instance->cs_pin == OUT_OF_RANGE_PIN_NUMBER ||
       p_instance->clk_pin == OUT_OF_RANGE_PIN_NUMBER ||
       p_instance->data_pin == OUT_OF_RANGE_PIN_NUMBER) {

       return FALSE;
    }

   
    if(!bcm2835_init()) {
       return FALSE;
    }

    bcm2835_gpio_fsel(p_instance->convst_pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(p_instance->cs_pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(p_instance->clk_pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(p_instance->data_pin, BCM2835_GPIO_FSEL_INPT);

 
    bcm2835_gpio_write(p_instance->cs_pin, HIGH);
    bcm2835_gpio_write(p_instance->clk_pin, LOW);
    bcm2835_gpio_write(p_instance->convst_pin, HIGH);

    return TRUE;
  }
  else {
    return BAD;
  }

}

void AD7091R_reset(AD7091R *p_instance) {

  if(p_instance != 0) {
    //Start a conversion
    delayMicroseconds(1);
    bcm2835_gpio_write(p_instance->convst_pin, LOW); //Set CONVST Pin to LOW
    delayMicroseconds(1);
    bcm2835_gpio_write(p_instance->convst_pin, HIGH);  //Set CONVST Pin to HIGH

    bcm2835_gpio_write(p_instance->cs_pin, LOW);        //Set CS Pin to LOW
    delayMicroseconds(1);

    uint8_t clock_cycle = 0;

    for(clock_cycle = 0; clock_cycle < 4; clock_cycle++) { //4 cycles only to short the cycle; you can choose between 2 to 8
      bcm2835_gpio_write(p_instance->clk_pin, HIGH); //Set CLK Pin to HIGH
      delayMicroseconds(1);
      bcm2835_gpio_write(p_instance->clk_pin, LOW); //Set CLK Pin to LOW
      delayMicroseconds(1);
    }

    bcm2835_gpio_write(p_instance->cs_pin, HIGH);

    //Perform Another conversion
    bcm2835_gpio_write(p_instance->convst_pin, LOW); //Set CONVST Pin to LOW
    delayMicroseconds(1);
    bcm2835_gpio_write(p_instance->convst_pin, HIGH);  //Set CONVST Pin to HIGH

    for(clock_cycle = 0; clock_cycle < 12; clock_cycle++) { 
      bcm2835_gpio_write(p_instance->clk_pin, HIGH); //Set CLK Pin to HIGH
      delayMicroseconds(1);
      bcm2835_gpio_write(p_instance->clk_pin, LOW); //Set CLK Pin to LOW
      delayMicroseconds(1);
    }

    return TRUE;
  }
  else {
    return FALSE;
  }
}

int AD7091R_data(AD7091R *p_instance) {
  
  if(p_instance != 0) {
    int result = 0;
  
    //Start a conversion
    bcm2835_gpio_write(p_instance->convst_pin, LOW); //Set CONVST Pin to LOW
    delayMicroseconds(1);
    bcm2835_gpio_write(p_instance->convst_pin, HIGH);  //Set CONVST Pin to HIGH
  
    bcm2835_gpio_write(p_instance->cs_pin, LOW);        //Set CS Pin to LOW
  
    uint8_t clock_cycle = 0;
    for(clock_cycle = 0; clock_cycle < 12; clock_cycle++) { 
      bcm2835_gpio_write(p_instance->clk_pin, HIGH); //Set CLK Pin to HIGH
      delayMicroseconds(1);
      bcm2835_gpio_write(p_instance->clk_pin, LOW); //Set CLK Pin to LOW
      result = (result << 1) | (bcm2835_gpio_lev(p_instance->data_pin) & 0x01);
      delayMicroseconds(1);
    }
  
    delayMicroseconds(1);
    bcm2835_gpio_write(p_instance->cs_pin, HIGH);

    return result;
  }
  else {
    return 0;
  }

}