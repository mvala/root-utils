#!/bin/bash

PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"

# Build
$PROJECT_DIR/scripts/make.sh install || exit $?

export LD_LIBRARY_PATH="$PROJECT_DIR/lib:$LD_LIBRARY_PATH"

MY_PWD=`pwd`
MY_RUN_DIR=$PROJECT_DIR/run/${1/.C/}
mkdir -p $MY_RUN_DIR

cd $MY_RUN_DIR
root -l $PROJECT_DIR/macros/MainRun.C'("'$PROJECT_DIR/$1'","'$PROJECT_DIR/'")'
cd $MY_PWD
