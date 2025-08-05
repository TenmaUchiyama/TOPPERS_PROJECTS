#!/bin/bash

# 引数チェック
if [ "$1" = "write" ]; then
    echo "write mode: skipping build, only uploading to microcontroller"
    cd obj
    echo "uploading asp.bin to stm32 microcontroller"
    st-flash --connect-under-reset write asp.bin 0x08000000
    exit 0
fi

# 通常のビルドモード
cd obj 

sh reset.sh
make 
make asp.bin 

echo "uploading asp.bin to stm32 microcontroller"

st-flash --connect-under-reset write asp.bin 0x08000000


