OUT_DIR = build

all: $(OUT_DIR)/rom.gba

build:
	@mkdir -p build

build/main.o: src/main.c ld/gba.ld | $(OUT_DIR)
	arm-none-eabi-gcc -mcpu=arm7tdmi -mthumb -O2 -c src/main.c -o $(OUT_DIR)/main.o

build/crt0.o: asm/crt0.s ld/gba.ld| $(OUT_DIR)
	arm-none-eabi-as asm/crt0.s -o $(OUT_DIR)/crt0.o

build/rom.elf: $(OUT_DIR)/main.o $(OUT_DIR)/crt0.o
	arm-none-eabi-ld -T ld/gba.ld -o $(OUT_DIR)/rom.elf $(OUT_DIR)/crt0.o $(OUT_DIR)/main.o

build/rom.gba: $(OUT_DIR)/rom.elf
	arm-none-eabi-objcopy -O binary $(OUT_DIR)/rom.elf $(OUT_DIR)/rom.gba

clean:
	@rm -rf $(OUT_DIR)
