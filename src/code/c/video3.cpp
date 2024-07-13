// Copyright (C) 2021 twyleg
#include <spidevpp/spi.h>
#include <stdlib.h> 
#include <unistd.h>
#include <iostream>

int main() {

	spidevpp::Spi spi("/dev/spidev0.0");
	spi.setBitsPerWord(8);
	spi.setSpeed(100000);
  
  char buf_in[4] = {0};
  spi.read(buf_in, 3);


  char buf_r[3] = {0};
  
  //spi.write(buf_r, 3);
  
  buf_r[0] = 3;
  buf_r[1] = 4;
  buf_r[2] = 5;
  spi.write(buf_r, 3);


  
  
  if(buf_in[0] != 0) std::cout << "Works\n";
  if(buf_in[1] == 0) std::cout << "Not Works\n";
  
}
