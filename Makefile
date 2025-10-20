CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=arm7tdmi -mthumb -O2 -Iinclude
LDFLAGS = -nostdlib -T ld/gba.ld

SRC_DIRS = src assets
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
DEPS = asm/crt0.s $(wildcard include/*.h) $(SRCS)

OUT_DIR = build

all: $(OUT_DIR)/rom.gba

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/rom.elf: $(DEPS) | $(OUT_DIR)
	$(CC) $(CFLAGS) asm/crt0.s $(SRCS) $(LDFLAGS) -o $@

$(OUT_DIR)/rom.gba: $(OUT_DIR)/rom.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(OUT_DIR)
