PROGRAM = main
PROGRAM_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Leave it empty if you don't want to use threadx
THREADX_EN = 1

# Any extra source files to include in the build. Use the upper case .S extension for assembly files
EXTRA_SRCS := 
# Any extra header files to include in the build. Add the path and don't forget the -I flag
# For example, a header which is in program dir: EXTRA_INCS := -I $(PROGRAM_DIR)
EXTRA_INCS := 

include ${PROGRAM_DIR}/bsp/common.mk