# Default pod makefile distributed with pods version: 12.11.14

.PHONY: default_target
default_target: all

# Default to a less-verbose build.  If you want all the gory compiler output,
# run "make VERBOSE=1"
$(VERBOSE).SILENT:

# Figure out where to build the software.
#   Use BUILD_PREFIX if it was passed in.
#   If not, search up to four parent directories for a 'build' directory.
#   Otherwise, use ./build.
ifeq "$(BUILD_PREFIX)" ""
BUILD_PREFIX:=$(shell for pfx in ./ .. ../.. ../../.. ../../../..; do d=`pwd`/$$pfx/build;\
               if [ -d $$d ]; then echo $$d; exit 0; fi; done; echo `pwd`/build)
endif
# create the build directory if needed, and normalize its path name
BUILD_PREFIX:=$(shell mkdir -p $(BUILD_PREFIX) && cd $(BUILD_PREFIX) && echo `pwd`)

# Default to a release build.  If you want to enable debugging flags, run
# "make BUILD_TYPE=Debug"
ifeq "$(BUILD_TYPE)" ""
BUILD_TYPE="Release"
endif

all: pod-build/Makefile
	$(MAKE) -C pod-build all install

pod-build/Makefile:
	$(MAKE) configure

.PHONY: configure
configure:
	@echo "\nBUILD_PREFIX: $(BUILD_PREFIX)\n\n"

	# create the temporary build directory if needed
	@mkdir -p pod-build

	# run CMake to generate and configure the build scripts
	@cd pod-build && cmake -DCMAKE_INSTALL_PREFIX=$(BUILD_PREFIX) \
		   -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DTIDY=${TIDY} ..

clean-all:
	-if [ -e pod-build/install_manifest.txt ]; then rm -f `cat pod-build/install_manifest.txt`; fi
	-if [ -d pod-build ]; then $(MAKE) -C pod-build clean; rm -rf pod-build; fi

clean:
	-if [ -e pod-build/install_manifest.txt ]; then rm -f `cat pod-build/install_manifest.txt`; fi
	-if [ -d pod-build ]; then $(MAKE) -C pod-build clean; fi

## USED TO CORRECT CODING STYLE OF CODE
format-python:
	@autopep8 --in-place -a -a -a --recursive ./python

format-cpp:
	@clang-format -i src/**/* include/**/*

format:
	$(MAKE) format-python
	$(MAKE) format-cpp

## USED TO CHECK CODING STYLE OF CODE
test-format-python:
	#this pipes to output if we set the output variable
	@eval "pycodestyle ./python $${OUTPUT:+"> ${OUTPUT}"}" || exit 0 

test-format-cpp:
	$(MAKE) clean
	$(MAKE) configure TIDY=1
	#this pipes to output if we set the output variable
	$(MAKE) $${OUTPUT:+"2> $${OUTPUT}"}

test-format:
	$(MAKE) test-format-python
	$(MAKE) test-format-cpp

## USED TO RUN TESTS
test-python:
	#this pipes to output if we set the output variable
	@eval "py.test  ./python $${OUTPUT:+"--junitxml ${OUTPUT}"}"

test-cpp:
	#this pipes to output if we set the output variable
	@eval "$(MAKE) test -C pod-build $${OUTPUT:+"ARGS=\"-T Test --no-compress-output\""}"

test:
	$(MAKE) test-python
	$(MAKE) test-cpp

## USED TO CHECK FOR MEMORY LEAKS
test-mem:
	cd build/test; 									\
	for dir in $$(find ! -path . -type d); 			\
	do 												\
		cd $${dir}; 								\
		for file in $$(find ./ -type f); 			\
		do 											\
			eval "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $${OUTPUT:+"--xml=yes --xml-file=$${file}.memcheck"} "$${file}""; \
		done; 										\
		cd ..; 										\
	done; 											\
	

# other (custom) targets are passed through to the cmake-generated Makefile
%::
	$(MAKE) -C pod-build $@