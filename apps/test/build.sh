#!/bin/bash


cd obj 

sh reset.sh
make 
make asp.bin 


echo "uploading asp.bin to stm32 microcontroller"

st-flash --connect-under-reset write asp.bin 0x08000000


