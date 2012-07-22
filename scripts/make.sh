#!/bin/bash

MY_PWD=`pwd`

PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"

if [ ! -d $PROJECT_DIR/build ];then
    mkdir -p $PROJECT_DIR/build
fi

cd $PROJECT_DIR/build

if [ ! -f Makefile ];then
  cmake -DCMAKE_INSTALL_PREFIX="$PROJECT_DIR" ../
fi

CMD="nice -n 15"

CMD="$CMD make $*"

$CMD

cd $MY_PWD