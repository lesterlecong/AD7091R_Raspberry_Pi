#include "AD7091R.h"
#include <stdio.h>
#include <unistd.h>

int main(void) {

  AD7091R rtd(5, 6, 13, 19); //CONVST, CS, CLK, DATA
  rtd.begin();
  rtd.reset();
  sleep(1);
  while(1) {
    printf("RTD Data: %d\n", rtd.data());
    
  }


  return 0;
}