CC = gcc
CFLAGS = -lm --std=c11 -O3 -g -Wall -Wextra
DPU_OPTS = `dpu-pkg-config --cflags --libs dpu`
TARGET = pim_hdc

# define DEBUG in the source if we are debugging
ifeq ($(DEBUG), 1)
	CFLAGS+=-DDEBUG
endif
# define TEST in the source if we are debugging
ifeq ($(TEST), 1)
	CFLAGS+=-DTEST
endif

SHOW_DPU_LOGS ?= 1
BULK_XFER ?= 1
COUNTER_CONFIG ?= "COUNT_CYCLES"

# define SHOW_DPU_LOGS in the source if we want DPU logs
ifeq ($(SHOW_DPU_LOGS), 1)
	CFLAGS+=-DSHOW_DPU_LOGS
endif

# define BULK_XFER if we want to use bulk transfers
ifeq ($(BULK_XFER), 1)
	CFLAGS+=-DBULK_XFER
endif

IM_IN_WRAM ?= 0

ifeq ($(IM_IN_WRAM), 1)
	CFLAGS+=-DIM_IN_WRAM
endif

CHAM_IN_WRAM ?= 0

ifeq ($(CHAM_IN_WRAM), 1)
	CFLAGS+=-DCHAM_IN_WRAM
endif

# Default
NR_DPUS ?= 32
NR_TASKLETS ?= 1

MAX_BIT_DIM ?= 313
MAX_CHANNELS ?= 4
MAX_N ?= 5
MAX_IM_LENGTH ?= 22
HDC_MAX_INPUT ?= 384

CFLAGS+=-DNR_DPUS=$(NR_DPUS) -DNR_TASKLETS=$(NR_TASKLETS) -DHOST=1
CFLAGS+=-DMAX_BIT_DIM=$(MAX_BIT_DIM) -DMAX_CHANNELS=$(MAX_CHANNELS)
CFLAGS+=-DMAX_N=$(MAX_N) -DMAX_IM_LENGTH=$(MAX_IM_LENGTH)
CFLAGS+=-DCOUNTER_CONFIG=$(COUNTER_CONFIG) -DHDC_MAX_INPUT=$(HDC_MAX_INPUT)

# For clock_gettime
CFLAGS += -D_POSIX_C_SOURCE=199309L

.PHONY: default all clean

default: $(TARGET) dpu
all: default

SOURCES = $(wildcard src/*.c) $(wildcard src/hdc/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
HEADERS = $(wildcard include/*.h)
INC=-Iinclude -IPIM-common/common/include -IPIM-common/host/include

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ $(DPU_OPTS)

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(INC) -o $@ $(DPU_OPTS)

dpu:
	DEBUG=$(DEBUG) NR_DPUS=$(NR_DPUS) NR_TASKLETS=$(NR_TASKLETS) \
	TEST=$(TEST) MAX_BIT_DIM=$(MAX_BIT_DIM) MAX_CHANNELS=$(MAX_CHANNELS) \
	MAX_N=$(MAX_N) MAX_IM_LENGTH=$(MAX_IM_LENGTH) \
	HDC_MAX_INPUT=$(HDC_MAX_INPUT) IM_IN_WRAM=$(IM_IN_WRAM) \
	CHAM_IN_WRAM=$(CHAM_IN_WRAM) COUNTER_CONFIG=$(COUNTER_CONFIG) \
	$(MAKE) -C src/dpu

clean:
	find . -type f -name '*.o' -delete
	-rm -f $(TARGET)
	$(MAKE) -C src/dpu clean
