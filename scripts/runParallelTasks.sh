#!/bin/bash

PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"

# Build
$PROJECT_DIR/scripts/make.sh install || exit $?

MY_PARALLEL=1
if [ -n "$1" ];then
  MY_PARALLEL=$1
fi
export LD_LIBRARY_PATH="$PROJECT_DIR/lib:$LD_LIBRARY_PATH"

MY_PWD=`pwd`
cd $PROJECT_DIR/macros/
root -l Test.C\($MY_PARALLEL\)
cd $MY_PWD
