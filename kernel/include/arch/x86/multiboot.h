#ifndef X86_MULTIBOOT_H
#define X86_MULTIBOOT_H

#include <typedef.h>

struct multiboot_header
{
    /* Must be MULTIBOOT_MAGIC - see above. */
    u32 magic;

    /* Feature flags. */
    u32 flags;

    /* The above fields plus this one must equal 0 mod 2^32. */
    u32 checksum;

    /* These are only valid if MULTIBOOT_AOUT_KLUDGE is set. */
    u32 header_addr;
    u32 load_addr;
    u32 load_end_addr;
    u32 bss_end_addr;
    u32 entry_addr;

    /* These are only valid if MULTIBOOT_VIDEO_MODE is set. */
    u32 mode_type;
    u32 width;
    u32 height;
    u32 depth;
};

/* The symbol table for a.out. */
struct multiboot_aout_symbol_table
{
    u32 tabsize;
    u32 strsize;
    u32 addr;
    u32 reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

/* The section header table for ELF. */
struct multiboot_elf_section_header_table
{
    u32 num;
    u32 size;
    u32 addr;
    u32 shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info
{
    u32 flags;
    u32 mem_lower;
    u32 mem_upper;
    u32 boot_device;
    u32 cmdline;
    u32 mods_count;
    u32 mods_addr;
    union
    {
        multiboot_aout_symbol_table_t aout_sym;
        multiboot_elf_section_header_table_t elf_sec;
    } u;
    u32 mmap_length;
    u32 mmap_addr;
    u32 drives_length;
    u32 drives_addr;
    u32 config_table;
    u32 boot_loader_name;
    u32 apm_table;
    u32 vbe_control_info;
    u32 vbe_mode_info;
    u16 vbe_mode;
    u16 vbe_interface_seg;
    u16 vbe_interface_off;
    u16 vbe_interface_len;
    u64 framebuffer_addr;
    u32 framebuffer_pitch;
    u32 framebuffer_width;
    u32 framebuffer_height;
    u8 framebuffer_bpp;
    u8 framebuffer_type;
    union
    {
        struct
        {
            u32 framebuffer_palette_addr;
            u16 framebuffer_palette_num_colors;
        };
        struct
        {
            u8 framebuffer_red_field_position;
            u8 framebuffer_red_mask_size;
            u8 framebuffer_green_field_position;
            u8 framebuffer_green_mask_size;
            u8 framebuffer_blue_field_position;
            u8 framebuffer_blue_mask_size;
        };
    };
};
typedef struct multiboot_info multiboot_info_t;
struct multiboot_color
{
    u8 red;
    u8 green;
    u8 blue;
};

struct multiboot_mmap_entry
{
    u32 size;
    u64 addr;
    u64 len;
    u32 type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_mod_list
{
    /* the memory used goes from bytes ’mod_start’ to ’mod_end-1’ inclusive */      u32 mod_start;
    u32 mod_end;

    /* Module command line */
    u32 cmdline;

    /* padding to take it to 16 bytes (must be zero) */
    u32 pad;
};
typedef struct multiboot_mod_list multiboot_module_t;

/* APM BIOS info. */
struct multiboot_apm_info
{
    u16 version;
    u16 cseg;
    u32 offset;
    u16 cseg_16;
    u16 dseg;
    u16 flags;
    u16 cseg_len;
    u16 cseg_16_len;
    u16 dseg_len;
};

#endif