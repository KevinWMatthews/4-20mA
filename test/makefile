#This makefile is currently rigged up to run the test executable ONLY,
#that is, make all will run the tests (just like make test).
#It will compile all of the source code in the process of doing this.

### User config ###
#To run tests, add them to this list
TESTS_TO_RUN= \
  Adc \
  AdcWiring \
  BitManip \
  ChipFunctions \
  LineFit \
  LedDigit \
  LedDigitWiring \
  LedNumber \
  LedNumberWiring \
  LedNumber \
  NumericFunctions \
  TimeService \
  TimeServiceWiring_ATtiny \


#Add the directory of the test's makefile (MakefileCppUTest.make) here
DEFAULT_DIR=.

ADC_DIR=Adc

ADCWIRING_DIR=AdcWiring

BITMANIP_DIR=BitManip

CHIPFUNCTIONS_DIR=ChipFunctions

LINEFIT_DIR=LineFit

LEDDIGIT_DIR=LedDigit

LEDDIGITWIRING_DIR=LedDigitWiring

LEDNUMBER_DIR=LedNumber

LEDNUMBERWIRING_DIR=LedNumberWiring

MAINLOOP_DIR=MainLoop

NUMERICFUNCTIONS_DIR=NumericFunctions

TIMESERVICE_DIR=TimeService

TIMESERVICEWIRING_ATTINY_DIR=TimeServiceWiring_ATtiny


#Create a makefile target for each series of tests
Default:
	$(MAKE_TESTS) $(DEFAULT_DIR) $(MAKECMDGOALS)

Adc:
	$(MAKE_TESTS) $(ADC_DIR) $(MAKECMDGOALS)

AdcWiring:
	$(MAKE_TESTS) $(ADCWIRING_DIR) $(MAKECMDGOALS)

BitManip:
	$(MAKE_TESTS) $(BITMANIP_DIR) $(MAKECMDGOALS)

ChipFunctions:
	$(MAKE_TESTS) $(CHIPFUNCTIONS_DIR) $(MAKECMDGOALS)

LineFit:
	$(MAKE_TESTS) $(LINEFIT_DIR) $(MAKECMDGOALS)

LedDigit:
	$(MAKE_TESTS) $(LEDDIGIT_DIR) $(MAKECMDGOALS)

LedDigitWiring:
	$(MAKE_TESTS) $(LEDDIGITWIRING_DIR) $(MAKECMDGOALS)

LedNumberWiring:
	$(MAKE_TESTS) $(LEDNUMBERWIRING_DIR) $(MAKECMDGOALS)

LedNumber:
	$(MAKE_TESTS) $(LEDNUMBER_DIR) $(MAKECMDGOALS)

MainLoop:
	$(MAKE_TESTS) $(MAINLOOP_DIR) $(MAKECMDGOALS)

NumericFunctions:
	$(MAKE_TESTS) $(NUMERICFUNCTIONS_DIR) $(MAKECMDGOALS)

TimeService:
	$(MAKE_TESTS) $(TIMESERVICE_DIR) $(MAKECMDGOALS)

TimeServiceWiring_ATtiny:
	$(MAKE_TESTS) $(TIMESERVICEWIRING_ATTINY_DIR) $(MAKECMDGOALS)



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
