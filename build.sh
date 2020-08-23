#clear for error messages
clear

# Assembly
nasm -felf32 kernel/source/boot/boot.asm -o kernel/object/boot.o

# C/C++ Compilation
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/kernel.c -o kernel/object/kernel.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/string.c -o kernel/object/string.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/stdlib.c -o kernel/object/stdlib.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/stdio.c  -o kernel/object/stdio.o 

gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/TTY.c    -o kernel/object/TTY.o    

# Link
gcc -m32 -I kernel/include/ -T .ld -o os.bin -ffreestanding -O2 -nostdlib \
kernel/object/boot.o   \
kernel/object/kernel.o \
kernel/object/string.o \
kernel/object/stdlib.o \
kernel/object/stdio.o  \
kernel/object/TTY.o    \

#test
export PATH=$PATH:/mnt/d/Program\ Files/qemu
qemu-system-x86_64.exe -kernel os.bin -monitor stdio