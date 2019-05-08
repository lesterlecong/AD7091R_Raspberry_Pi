#include "AD7091R.h"
#include <stdio.h>
#include <unistd.h>

int main(void) {

  AD7091R rtd(5, 6, 13, 19); //CONVST, CS, CLK, DATA
  AD7091R adc(5, 20, 13, 21);

  rtd.begin();
  rtd.reset();

  adc.begin();
  adc.reset();

  sleep(1);
  while(1) {
    printf("ADC Data: %d\n", adc.data());
    usleep(500);
  }


  return 0;
}