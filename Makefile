kernel_source_files := $(shell find src/system -name *.cpp)
kernel_object_files := $(patsubst src/system/%.cpp, build/system/%.o, $(kernel_source_files))

lib_c_source_files := $(shell find src/lib/ -name *.cpp)
lib_c_object_files := $(patsubst src/lib/%.cpp, build/lib/%.o, $(lib_c_source_files))

lib_asm_source_files := $(shell find src/lib -name *.asm)
lib_asm_object_files := $(patsubst src/lib/%.asm, build/lib/%.o, $(lib_asm_source_files))

boot_source_files := $(shell find src/boot/ -name *.asm)
boot_object_files := $(patsubst src/boot/%.asm, build/boot/%.o, $(boot_source_files))

x86_64_object_files := $(lib_c_object_files) $(lib_asm_object_files) $(boot_object_files)


$(kernel_object_files): build/system/%.o : src/system/%.cpp
	mkdir -p $(dir $@) && \
	g++ -c -I src/lib -ffreestanding $(patsubst build/system/%.o, src/system/%.cpp, $@) -o $@


$(lib_c_object_files): build/lib/%.o : src/lib/%.cpp
	mkdir -p $(dir $@) && \
	g++ -c -I src/lib -ffreestanding $(patsubst build/lib/%.o, src/lib/%.cpp, $@) -o $@

$(lib_asm_object_files): build/lib/%.o : src/lib/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/lib/%.o, src/lib/%.asm, $@) -o $@

$(boot_object_files): build/boot/%.o : src/boot/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/boot/%.o, src/boot/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

clean:
	@echo Cleaning Files....
	rm -r -v build dist