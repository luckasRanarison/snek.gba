CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
C_FLAGS = -mcpu=arm7tdmi -mthumb -nostdlib -O2 -T ld/gba.ld
OUT_DIR = build

all: $(OUT_DIR)/rom.gba

build:
	@mkdir -p build

build/rom.elf: asm/crt0.s $(wildcard src/*.c) $(wildcard assets/**) | $(OUT_DIR)
	$(CC) $(C_FLAGS) asm/crt0.s src/*.c assets/*.c -o $(OUT_DIR)/rom.elf

build/rom.gba: $(OUT_DIR)/rom.elf
	$(OBJCOPY) -O binary $(OUT_DIR)/rom.elf $(OUT_DIR)/rom.gba

clean:
	@rm -rf $(OUT_DIR)
