#include "AD7091R.h"
#include <stdio.h>
#include <unistd.h>

int main(void) {

  AD7091R rtd(21, 22, 23, 24); //CONVST, CS, CLK, DATA
  rtd.begin();
  rtd.reset();
  sleep(1);
  rtd.data();


  return 0;
}