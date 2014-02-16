# ********************************************************************************************
#
#	Makefile for building projects which make use of ARM Cortex-M0/3/4-based microcontrolleres
#
# ********************************************************************************************
#
# Makefile rules:
#
# make all = Create project files.
#
# make clean = Clean project files.
#
# make rebuild = Rebuild project files.
#
# ********************************************************************************************
#
# Author: Henrique Persico Rossi
# e-mail: henriqueprossi@gmail.com
#
# ********************************************************************************************

# ********************************************************************************************
# Environment variables
# ********************************************************************************************

PROJECT_DIR            = $(shell pwd)
#TOOLCHAIN_DIR          = /opt/toolchains/eabi/gcc-arm-none-eabi-4_7-2013q3/bin
TOOLCHAIN_DIR          = /opt/toolchains/eabi/arm-2013.11/bin
TARGET_PREFIX          = $(TOOLCHAIN_DIR)/arm-none-eabi-
OUTPUT_DIR             = $(PROJECT_DIR)/build
CMSIS_DIR              = $(PROJECT_DIR)/Libraries/CMSIS
STM32F4_STD_PERIPH_DIR = $(PROJECT_DIR)/Libraries/STM32F4xx_StdPeriph_Driver
FREERTOS_DIR           = $(PROJECT_DIR)/FreeRTOS/Source

# ********************************************************************************************
# Toolchain binaries
# ********************************************************************************************

CC      = $(TARGET_PREFIX)gcc
OBJCOPY = $(TARGET_PREFIX)objcopy
ASM     = $(TARGET_PREFIX)gcc -x assembler-with-cpp
NM      = $(TARGET_PREFIX)nm
OBJDUMP = $(TARGET_PREFIX)objdump
HEX     = $(OBJCOPY) -O ihex
BIN     = $(OBJCOPY) -O binary

# ********************************************************************************************
# MCU flags
# ********************************************************************************************

# MCU which is used in this project. Availables ARM Cortex-Mx cores:
# ARM_CORTEX_M0
# ARM_CORTEX_M3
# ARM_CORTEX_M4

USED_ARM_CORTEX_MX = ARM_CORTEX_M4

ifeq ($(USED_ARM_CORTEX_MX), ARM_CORTEX_M0)
MCU_FLAGS = -mcpu=cortex-m0 -mtune=cortex-m0
else ifeq ($(USED_ARM_CORTEX_MX), ARM_CORTEX_M3)
MCU_FLAGS = -mcpu=cortex-m3 -mtune=cortex-m3
else ifeq ($(USED_ARM_CORTEX_MX), ARM_CORTEX_M4)
#MCU_FLAGS = -march=armv7 -mcpu=cortex-m4 -mfloat-abi=soft
MCU_FLAGS = -mcpu=cortex-m4 -mtune=cortex-m4 -mfloat-abi=hard
else

endif

# Thumb mode is enabled
MCU_FLAGS += -mthumb

# ********************************************************************************************
# Project variables
# ********************************************************************************************

# Project name
PROJECT = hello_world

# Define linker script file
LDSCRIPT = $(PROJECT_DIR)/project/stm32f4_flash.ld

BUILD_NAME = $(PROJECT)

# Project's space-delimited list of C source files
PROJ_C_SRC = $(PROJECT_DIR)/src/system_stm32f4xx.c            \
             $(PROJECT_DIR)/src/crt.c                         \
             $(PROJECT_DIR)/src/stm32f4_vector.c              \
             $(PROJECT_DIR)/src/hello_world.c                 \
             $(PROJECT_DIR)/src/stm32f4_discovery.c           \
             $(STM32F4_STD_PERIPH_DIR)/src/stm32f4xx_rcc.c    \
             $(STM32F4_STD_PERIPH_DIR)/src/stm32f4xx_gpio.c   \
             $(STM32F4_STD_PERIPH_DIR)/src/stm32f4xx_syscfg.c \
             $(STM32F4_STD_PERIPH_DIR)/src/stm32f4xx_exti.c   \
             $(STM32F4_STD_PERIPH_DIR)/src/misc.c             \
             $(FREERTOS_DIR)/event_groups.c                   \
             $(FREERTOS_DIR)/list.c                           \
             $(FREERTOS_DIR)/queue.c                          \
             $(FREERTOS_DIR)/tasks.c                          \
             $(FREERTOS_DIR)/timers.c                         \
             $(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c     \
             $(FREERTOS_DIR)/portable/MemMang/heap_2.c

# Project's space-delimited list of ASM source files
PROJ_ASM_SRC =

# Project's space-delimited list all directories
PROJ_INC_DIR = $(PROJECT_DIR)                        \
               $(PROJECT_DIR)/src                    \
               $(PROJECT_DIR)/project                \
               $(CMSIS_DIR)/Include                  \
               $(STM32F4_STD_PERIPH_DIR)/inc         \
               $(FREERTOS_DIR)/include               \
               $(FREERTOS_DIR)/portable/GCC/ARM_CM4F

# Project's list of directories for library search
PROJ_LIB_DIR = project

# Project's list of necessary libraries
PROJ_LIBS =

# Project's space-delimited list of C #define's in the following forms: XXXXX or XXXXX=Y
PROJ_C_DEFINES = USE_STDPERIPH_DRIVER STM32F40_41xxx
#STM32F4XX

# Project's space-delimited list of ASM #define's in the following forms: XXXXX or XXXXX=Y
PROJ_ASM_DEFINES =

INCDIR      = $(patsubst %,-I%,$(PROJ_INC_DIR))
LIBDIR      = $(patsubst %,-L%,$(PROJ_LIB_DIR))
C_DEFINES   = $(patsubst %,-D%,$(PROJ_C_DEFINES))
ASM_DEFINES = $(patsubst %,-D%,$(PROJ_ASM_DEFINES))

# Debug information flags
DEBUG = -g

# Code optimization level
OPT = -O0

# Flags which are used by the ASM compiler
ASMFLAGS = -c $(DEBUG) $(MCU_FLAGS) -Wa,-amhls=$(addprefix $(OUTPUT_DIR)/, $(notdir $(addsuffix .lst, $(basename $<)))) $(ASM_DEFINES)

# Flags which are used by the C compiler
CFLAGS = -c $(DEBUG) $(OPT) $(MCU_FLAGS) -mapcs-frame -Wall -Wstrict-prototypes -fverbose-asm $(C_DEFINES)

# Generate dependency information
CFLAGS += -MMD -MP -MF $(OUTPUT_DIR)/.dep/$(@F).d

# Generate assembly list
CFLAGS += -Wa,-adhlns=$(addprefix $(OUTPUT_DIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

# Flags which are used by the linker
LDFLAGS = $(MCU_FLAGS) -nostartfiles -Wl,-T$(LDSCRIPT) -Wl,-Map=$(OUTPUT_DIR)/$(BUILD_NAME).map,--cref,--no-warn-mismatch $(LIBDIR)

LDFLAGS += -lgcc -lc
#LDFLAGS += -Wl,--start-group -lgcc -lc -lc -lm -lnosys -Wl,--end-group
#-nostdlib
# Implementations of semihosting:
# 	for Linaro:-lrdimon
#   for Sourcery CodeBench Lite: -lcs3unhosted and -lcs3hosted

# List of all source files in the project (ASM and C files)
ALL_PROJ_SRC = $(PROJ_ASM_SRC) $(PROJ_C_SRC)

# List of all source files in the project without directory and file-extension information
ALL_PROJ_SRC_BASE = $(notdir $(basename $(ALL_PROJ_SRC)))

# List of all object files, which are stored at the OUTPUT_DIR directory
ALL_PROJ_OBJS := $(addprefix $(OUTPUT_DIR)/,$(addsuffix .o,$(ALL_PROJ_SRC_BASE)))

###################################################################################
# Makefile targets
###################################################################################

.PHONY: all clean build rebuild elf list sym hex bin create_build_dirs program

# Default target in the absence of any target on running make
all: build
	

create_build_dirs:
	mkdir -p $(OUTPUT_DIR)
	mkdir -p $(OUTPUT_DIR)/.dep

# Targets for the build-sequence
build: create_build_dirs elf list sym hex bin

# Targets for building the output binary files individually
elf:  $(OUTPUT_DIR)/$(BUILD_NAME).elf
list: $(OUTPUT_DIR)/$(BUILD_NAME).list 
sym:  $(OUTPUT_DIR)/$(BUILD_NAME).sym
hex:  $(OUTPUT_DIR)/$(BUILD_NAME).hex
bin:  $(OUTPUT_DIR)/$(BUILD_NAME).bin

# Rebuild upon makefile changes
BUILDONCHANGE = makefile

rebuild: clean build

.SECONDARY : elf
.PRECIOUS : $(ALL_PROJ_OBJS)
%.elf: $(ALL_PROJ_OBJS) $(BUILDONCHANGE)
	$(CC) $(ALL_PROJ_OBJS) $(LDFLAGS) -o $@

%.hex: %.elf $(BUILDONCHANGE)
	$(HEX) $< $@

%.bin: %.elf $(BUILDONCHANGE)
	$(BIN) $< $@

# Create the symbol table from the built ELF output file
%.sym: %.elf $(BUILDONCHANGE)
	$(NM) -n $< > $@

# Create a listing file from the built ELF output file
%.list: %.elf $(BUILDONCHANGE)
	$(OBJDUMP) -x -S -C $< > $@

# Compile assembly-language source code
define ASSEMBLY_FILE_RULE_TEMPLATE
$(OUTPUT_DIR)/$(notdir $(basename $(1))).o : $(1) $(BUILDONCHANGE)
	$(ASM) $$(ASMFLAGS) $$< -o $$@
endef
$(foreach src, $(PROJ_ASM_SRC), $(eval $(call ASSEMBLY_FILE_RULE_TEMPLATE, $(src)))) 

# Compile C-language source code
define C_FILE_RULE_TEMPLATE
$(OUTPUT_DIR)/$(notdir $(basename $(1))).o : $(1) $(BUILDONCHANGE)
	$(CC) $$(CFLAGS) $(INCDIR) $$< -o $$@
endef
$(foreach src, $(PROJ_C_SRC), $(eval $(call C_FILE_RULE_TEMPLATE, $(src))))

clean:
	-rm -Rf $(OUTPUT_DIR)

# Include the dependency files.
-include $(wildcard $(OUTDIR)/.dep/*.d)

