CC = arm-none-eabi-gcc
SIZE = arm-none-eabi-size

BUILD_DIR = build

SRCS = App/app.c \
       Core/Src/startup.c \
       Core/Src/vector.c \
       Core/Src/clock_config.c \
       Core/Src/rcc.c \
       Drivers/Src/gpio.c

INCLUDES = -ICore/Inc -IDrivers/Inc 

CFLAGS = -mcpu=cortex-m3 \
         -mthumb \
         -std=c11 \
         -Wall \
         -Wextra \
         -g \
         -O0 \
         -ffunction-sections \
         -fdata-sections \
         -MMD \
         -MP \
         $(INCLUDES)

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)


.PHONY: all clean

all: $(BUILD_DIR)/firmware.elf


# Compile
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# Link
$(BUILD_DIR)/firmware.elf: $(OBJS) stm32f103.ld
	$(CC) $(CFLAGS) \
	    -nostdlib \
	    -T stm32f103.ld \
	    -Wl,-Map=$(BUILD_DIR)/firmware.map \
	    $(OBJS) -o $@
	$(SIZE) $@


# Clean
clean:
	rm -rf $(BUILD_DIR)


# Header dependencies
-include $(DEPS)
