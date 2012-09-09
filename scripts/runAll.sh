#!/bin/bash

PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"

# Build
$PROJECT_DIR/scripts/make.sh install || exit $?

export LD_LIBRARY_PATH="$PROJECT_DIR/lib:$LD_LIBRARY_PATH"

MY_PWD=`pwd`
MY_RUN_DIR=$PROJECT_DIR/run/${1/.C/}
rm -Rf $MY_RUN_DIR
mkdir -p $MY_RUN_DIR

cd $MY_RUN_DIR
cp $PROJECT_DIR/$1 .
MACRO=$(basename $1)
root -l $PROJECT_DIR/macros/MainRun.C'("'$MACRO'","'$PROJECT_DIR/'")'
cd $MY_PWD
