COMMON_DIR 		   := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
THREADX_PORT_DIR   := ${PROGRAM_DIR}/threadx/ports/risc-v32/gnu/src
THREADX_COMMON_DIR := ${PROGRAM_DIR}/threadx/common/src

TX_ASM_SRCS		   := $(wildcard ${THREADX_PORT_DIR}/*.S)
TX_THREAD_SRCS     := $(wildcard ${THREADX_COMMON_DIR}/tx_thread_*.c)
TX_TIMER_SRCS      := $(wildcard ${THREADX_COMMON_DIR}/tx_time*.c)
TX_INIT_SRCS       := $(wildcard ${THREADX_COMMON_DIR}/tx_initialize_*.c)
TX_EF_SRCS         := $(wildcard ${THREADX_COMMON_DIR}/tx_event_flags_*.c)
TX_QUEUE_SRCS      := $(wildcard ${THREADX_COMMON_DIR}/tx_queue_*.c)
TX_SEMAPHORE_SRCS  := $(wildcard ${THREADX_COMMON_DIR}/tx_semaphore_*.c)
TX_MUTEX_SRCS      := $(wildcard ${THREADX_COMMON_DIR}/tx_mutex_*.c)

COMMON_SRCS  		= $(wildcard $(COMMON_DIR)/src/*.c)
COMMONS_INCS 	    = $(COMMON_DIR)/inc
TX_SRCS 		   := ${TX_ASM_SRCS} ${TX_THREAD_SRCS} ${TX_TIMER_SRCS} ${TX_INIT_SRCS} \
			  	      ${TX_EF_SRCS}  ${TX_QUEUE_SRCS}  ${TX_MUTEX_SRCS} ${TX_SEMAPHORE_SRCS}  
TX_INCS 	       := -I${PROGRAM_DIR}/threadx/common/inc -I${PROGRAM_DIR}/threadx/ports/risc-v32/gnu/inc

ARCH = rv32im 

ifdef PROGRAM
PROGRAM_C := $(PROGRAM).c
endif

ifdef THREADX_EN
SRCS = $(COMMON_SRCS) $(PROGRAM_C) $(EXTRA_SRCS) $(TX_SRCS)
INCS = -I$(COMMONS_INCS) $(EXTRA_INCS) $(TX_INCS)
else
SRCS = $(COMMON_SRCS) $(PROGRAM_C) $(EXTRA_SRCS) 
INCS = -I$(COMMONS_INCS) $(EXTRA_INCS)
endif

C_SRCS   = $(filter %.c, $(SRCS))
ASM_SRCS = $(filter %.S, $(SRCS))

CC = riscv32-unknown-elf-gcc

OBJCOPY ?= $(subst gcc,objcopy,$(wordlist 1,1,$(CC)))
OBJDUMP ?= $(subst gcc,objdump,$(wordlist 1,1,$(CC)))

LINKER_SCRIPT ?= $(COMMON_DIR)/linker.ld
CRT ?= $(COMMON_DIR)/src/crt0.S
CFLAGS ?= -march=$(ARCH) -mabi=ilp32 -mcmodel=medany -Wall -g -O0\
	-fvisibility=hidden -nostdlib -nostartfiles $(PROGRAM_CFLAGS)

OBJS := ${C_SRCS:.c=.o} ${ASM_SRCS:.S=.o} ${CRT:.S=.o}
DEPS = $(OBJS:%.o=%.d)

ifdef PROGRAM
OUTFILES := $(PROGRAM).elf 
else
OUTFILES := $(OBJS)
endif

all: $(OUTFILES)

ifdef PROGRAM
$(PROGRAM).elf: $(OBJS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) -T $(LINKER_SCRIPT) $(OBJS) -o $@ $(LIBS)

.PHONY: disassemble
disassemble: $(PROGRAM).dis
endif

%.dis: %.elf
	$(OBJDUMP) -SD $^ > $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $(INCS) -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -MMD -c $(INCS) -o $@ $<

clean:
	$(RM) -f $(OBJS) $(DEPS) $(PROGRAM).elf $(PROGRAM).dis
