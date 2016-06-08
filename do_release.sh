#!/bin/bash
set -e

# Change to the directory where the script is located.  This is top level
# of project.
cd $(dirname $0)

# Clean out all .o files before we begin.
find . -type f          \
     -name "*.a"   -o   \
     -name "*.bin" -o   \
     -name "*.d"   -o   \
     -name "*.dis" -o   \
     -name "*.elf" -o   \
     -name "*.hex" -o   \
     -name "*.lst" -o   \
     -name "*.map" -o   \
     -name "*.o"   -o   \
     -name "*.sym" -o   \
     -name "*.zip"      \
    | xargs rm -f

source version.mk

SAM7S_BASE_DIR=SAM7s_base
RCP_DIST_DIR=firmware_release
NUM_PROC=$(grep -c proc /proc/cpuinfo)
MAX_MK1_ELF_SIZE=229376

RELEASE_NAME_SUFFIX=$(git describe --dirty --always)

rm -rf $RCP_DIST_DIR
mkdir $RCP_DIST_DIR

##################################
# TEST FIRST!!!
##################################
pushd test
make clean
make -j $NUM_PROC
./rcptest
popd

###################################
# MK1 release
###################################
pushd lib_lua
make PLAT=sam7s clean
make PLAT=sam7s generic -j $NUM_PROC
popd
make PLAT=sam7s clean
make PLAT=sam7s all -j $NUM_PROC

sh ./check_elf_size.sh main.elf arm-elf-size $MAX_MK1_ELF_SIZE

RELEASE_NAME=RaceCapturePro_MK1_$RELEASE_NAME_SUFFIX
RELEASE_DIR=$RELEASE_NAME
TMP_DIR=$(mktemp -d)
RELEASE_DIR_PATH="${TMP_DIR}/${RELEASE_DIR}"
mkdir -p $RELEASE_DIR_PATH

cp CHANGELOG $RELEASE_DIR_PATH
cp SAM7s_base/HOW_TO_FLASH.txt $RELEASE_DIR_PATH
cp $SAM7S_BASE_DIR/installer/* $RELEASE_DIR_PATH
cp main.elf $RELEASE_DIR_PATH/$RELEASE_NAME.elf
(cd $TMP_DIR; zip -9FSr $RELEASE_NAME.zip $RELEASE_DIR)

cp $TMP_DIR/$RELEASE_NAME.zip .
rm -rf $TMP_DIR
exit 0
