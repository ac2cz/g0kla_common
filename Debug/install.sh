#!/bin/bash

LIB_DIR=/usr/local/lib/
INC_DIR=/usr/local/include/g0kla_common

if [ ! -d $LIB_DIR ]; then
    mkdir $LIB_DIR
fi
if [ ! -d $INC_DIR ]; then
    mkdir $INC_DIR
fi

cp ../inc/*.h $INC_DIR
cp libg0kla_common.so $LIB_DIR
