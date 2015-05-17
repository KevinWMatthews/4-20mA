#This makefile is currently rigged up to run the test executable ONLY,
#that is, make all will run the tests (just like make test).
#It will compile all of the source code in the process of doing this.

### User config ###
#To run tests, add them to this list
TESTS_TO_RUN=Default

#Add the directory of the test's makefile (MakefileCppUTest.make) here
DEFAULT_DIR=.

#Create a makefile target for each series of tests
Default:
	$(MAKE_TESTS) $(DEFAULT_DIR) $(MAKECMDGOALS)

### Makefile targets ###
.DEFAULT_GOAL:=all

.PHONY: $(TESTS_TO_RUN)
.PHONY: all test clean rebuild rebuildt
.PHONY: filelist dirlist flags colortest help

all: $(TESTS_TO_RUN)

test: $(TESTS_TO_RUN)

clean: $(TESTS_TO_RUN)

rebuild: clean all

rebuildt: clean test

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
