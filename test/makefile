#This makefile is currently rigged up to run the test executable ONLY,
#that is, make all will run the tests (just like make test).
#It will compile all of the source code in the process of doing this.

### User config ###
#To run tests, add them to this list
TESTS_TO_RUN=MainLoop

#Add the directory of the test's makefile (MakefileCppUTest.make) here
DEFAULT_DIR=.

ATOD_DIR=AtoD

ADC_DIR=Adc

LINEFIT_DIR=LineFit

LEDDIGIT_DIR=LedDigit

LEDNUMBER_DIR=LedNumber

TIMESERVICE_DIR=TimeService

MAINLOOP_DIR=MainLoop

NUMERICFUNCTIONS_DIR=NumericFunctions

#Create a makefile target for each series of tests
Default:
	$(MAKE_TESTS) $(DEFAULT_DIR) $(MAKECMDGOALS)

AtoD:
	$(MAKE_TESTS) $(ATOD_DIR) $(MAKECMDGOALS)

Adc:
	$(MAKE_TESTS) $(ADC_DIR) $(MAKECMDGOALS)

LineFit:
	$(MAKE_TESTS) $(LINEFIT_DIR) $(MAKECMDGOALS)

LedDigit:
	$(MAKE_TESTS) $(LEDDIGIT_DIR) $(MAKECMDGOALS)

LedNumber:
	$(MAKE_TESTS) $(LEDNUMBER_DIR) $(MAKECMDGOALS)

TimeService:
	$(MAKE_TESTS) $(TIMESERVICE_DIR) $(MAKECMDGOALS)

MainLoop:
	$(MAKE_TESTS) $(MAINLOOP_DIR) $(MAKECMDGOALS)

NumericFunctions:
	$(MAKE_TESTS) $(NUMERICFUNCTIONS_DIR) $(MAKECMDGOALS)

### Makefile targets ###
.DEFAULT_GOAL:=all

.PHONY: $(TESTS_TO_RUN)
.PHONY: all test clean rebuild rtest
.PHONY: filelist dirlist flags colortest help

all: $(TESTS_TO_RUN)

test: $(TESTS_TO_RUN)

clean: $(TESTS_TO_RUN)

rebuild: clean all

rtest: clean test

# Compile and run production code
# run: $(TESTS_TO_RUN)

#Makefile debug options
filelist: $(TESTS_TO_RUN)

dirlist: $(TESTS_TO_RUN)

flags: $(TESTS_TO_RUN)

vars: $(TESTS_TO_RUN)

colortest: Default

help: Default


### Helpers ###
#NOTE: You must specify a directory immediately after MAKE_TESTS!
# -C  Change Directory
MAKE_TESTS=make --file MakefileCppUTest.make -C


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
