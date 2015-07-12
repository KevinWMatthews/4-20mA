#!/bin/bash

NAME=$1
PROJECT=$2

TEST_PREFIX=Test_

#Directories
TEMPLATE_DIR=Templates
DEFAULT_OUTPUT_DIR=.
#Output directory is set later

#Files
TEMPLATE_C_FILE=Template.c
TEMPLATE_H_FILE=Template.h
TEMPLATE_TEST_CPP_FILE=Test_Template.cpp
TEMPLATE_TEST_H_FILE=Test_Template.h
TEMPLATE_MAKEFILE=MakefileCppUTest.make
TEMPLATE_TEST_RUNNER=AllTests.cpp



#Functions
function yes_no ()
{
  source ./HelperScripts/yes_no_function.sh "$1" $2
}

GenerateFile()
{
  if [ -f $2 ]; then
    echo "$2 already exists! Skipping."
  else
    echo "Creating $2"
    sed $SUBSTITUTE_NAME <$1 >$2
  fi
}



####################
### Script start ###
####################
while [ -z "$NAME" ]
do
  read -p "Please enter a module name: " NAME
done

OUTPUT_C_FILE="$NAME".c
OUTPUT_H_FILE="$NAME".h
OUTPUT_TEST_CPP_FILE=$TEST_PREFIX"$NAME".cpp
OUTPUT_TEST_H_FILE=$TEST_PREFIX"$NAME".h
OUTPUT_MAKEFILE=MakefileCppUTest.make

SUBSTITUTE_NAME="s/<Name>/$NAME/g"

if yes_no "Generate source files?" Y; then
  GenerateFile $TEMPLATE_DIR/$TEMPLATE_C_FILE $DEFAULT_OUTPUT_DIR/$OUTPUT_C_FILE
  GenerateFile $TEMPLATE_DIR/$TEMPLATE_H_FILE $DEFAULT_OUTPUT_DIR/$OUTPUT_H_FILE
  echo
fi

if yes_no "Generate test directory?" Y; then
  OUTPUT_DIR="$NAME"
  OUTPUT_SRC_DIR=$OUTPUT_DIR/src
  OUTPUT_INC_DIR=$OUTPUT_DIR/inc

  mkdir -p $OUTPUT_DIR
  mkdir -p $OUTPUT_SRC_DIR
  mkdir -p $OUTPUT_INC_DIR

  while [ -z "$PROJECT" ]
  do
    read -p "Please enter a project name: " PROJECT
  done

  SUBSTITUTE_PROJECT="s/<Project>/$PROJECT/g"

  #Copy test runner
  echo "Creating $TEMPLATE_TEST_RUNNER"
  cp $TEMPLATE_DIR/$TEMPLATE_TEST_RUNNER $OUTPUT_SRC_DIR/$TEMPLATE_TEST_RUNNER

  #Generate Makefile
  GenerateFile $TEMPLATE_DIR/$TEMPLATE_MAKEFILE $OUTPUT_DIR/$OUTPUT_MAKEFILE
  sed -i $SUBSTITUTE_PROJECT $OUTPUT_DIR/$OUTPUT_MAKEFILE
  echo
else
  OUTPUT_DIR=$DEFAULT_OUTPUT_DIR
  OUTPUT_SRC_DIR=$DEFAULT_OUTPUT_DIR
  OUTPUT_INC_DIR=$DEFAULT_OUTPUT_DIR
fi

if yes_no "Generate test code?" Y; then
  #Generate files in src folder
  GenerateFile $TEMPLATE_DIR/$TEMPLATE_TEST_CPP_FILE $OUTPUT_SRC_DIR/$OUTPUT_TEST_CPP_FILE

  #Generate files in inc folder
  GenerateFile $TEMPLATE_DIR/$TEMPLATE_TEST_H_FILE $OUTPUT_INC_DIR/$OUTPUT_TEST_H_FILE
fi
