#clear for error messages
clear

# Assembly
nasm -felf32 kernel/source/boot/boot.asm -o kernel/object/boot.o

# C/C++ Compilation
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/kernel.c -o kernel/object/kernel.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/string.c -o kernel/object/string.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/stdlib.c -o kernel/object/stdlib.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/stdio.c  -o kernel/object/stdio.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/time.c   -o kernel/object/time.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/CPUID.c  -o kernel/object/CPUID.o 
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/VFS.c    -o kernel/object/VFS.o 

gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/TTY.c    -o kernel/object/TTY.o    
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/VBE.c    -o kernel/object/VBE.o    
gcc -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include/ -c kernel/source/UI.c     -o kernel/object/UI.o    

# Link
gcc -m32 -I kernel/include/ -T .ld -o os.bin -ffreestanding -O2 -nostdlib \
kernel/object/boot.o   \
kernel/object/kernel.o \
kernel/object/string.o \
kernel/object/stdlib.o \
kernel/object/stdio.o  \
kernel/object/time.o   \
kernel/object/CPUID.o  \
kernel/object/VFS.o    \
kernel/object/TTY.o    \
kernel/object/VBE.o    \
kernel/object/UI.o     \

cp os.bin isodir/boot/os.bin
grub-mkrescue -o os.iso isodir

#test
if   [[ "$OSTYPE" == "linux-gnu"* ]]; then                   # 
    if grep -1 Microsoft /proc/version; then                 #
        export PATH=$PATH:/mnt/d/Program\ Files/qemu         # WSL
        qemu-system-x86_64.exe -cdrom os.iso -monitor stdio #
    else                                                     #
        qemu-system-x86_64 -kernel os.bin -monitor stdio     # Linux 
    fi                                                       #
elif [[ "$OSTYPE" == "darwin"* ]];  then                     #
    qemu-system-x86_64 -kernel os.bin -monitor stdio         # MacOS
fi                                                           #
