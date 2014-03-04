/*
 * Library functions to read and write the S3C2416 registers
 *
 */

#include "s3cregisters.h"
#define MAP_SIZE 4096
#define MAP_MASK ( MAP_SIZE - 1 )
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)    /* Don't print in release builds */
#endif

struct reg_info {
    char *name;
    u32 addr;
    int shift;
    u32 mask;
    char type;
    char *desc;
};


static struct reg_info regs[] = {
    { "GPACON_15", 0x56000000, 15, 0x00000001, 'x', "GPIO PORT A pin 15 configuration" },
    { "GPACON_16", 0x56000000, 16, 0x00000001, 'x', "GPIO PORT A pin 16 configuration" },
    { "GPADAT_15", 0x56000004, 15, 0x00000001, 'd', "GPIO PORT A pin 15 data" },
    { "GPADAT_16", 0x56000004, 16, 0x00000001, 'd', "GPIO PORT A pin 15 data" },
};

static u32 readmem(u32 addr)
{
    void *map, *regaddr;
    u32 val;
    int fd = -1;

    DEBUG_PRINT("readmem(0x%08x)\n", addr);

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd<0) {
        perror("open(\"/dev/mem\")");
        exit(1);
    }

    map = mmap(0,
               MAP_SIZE,
               PROT_READ | PROT_WRITE,
               MAP_SHARED,
               fd,
               addr & ~MAP_MASK
               );
    if (map == (void*)-1 ) {
        perror("mmap()");
        exit(1);
    }

    regaddr = map + (addr & MAP_MASK);

    val = *(u32*) regaddr;
    munmap(map,MAP_SIZE);
    close(fd);

    return val;
}

static void writemem(u32 addr, u32 val)
{
    void *map, *regaddr;
    int fd = -1;

    DEBUG_PRINT("writemem(0x%08x, 0x%08x)\n", addr, val);

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd<0) {
        perror("open(\"/dev/mem\")");
        exit(1);
    }

    map = mmap(0,
               MAP_SIZE,
               PROT_READ | PROT_WRITE,
               MAP_SHARED,
               fd,
               addr & ~MAP_MASK
               );
    if (map == (void*)-1 ) {
        perror("mmap()");
        exit(1);
    }

    regaddr = map + (addr & MAP_MASK);

    *(u32*) regaddr = val;
    munmap(map,MAP_SIZE);
    close(fd);
}

u32 readreg(int i)
{
    volatile u32 mem = 0;
    u32 regdata = 0;
    mem = readmem(regs[i].addr);
    DEBUG_PRINT("Read Old contents: 0x%08x\n", mem);
    regdata = (mem >> regs[i].shift) & regs[i].mask;
    DEBUG_PRINT("Read Masked contents: 0x%08x\n", regdata);
    return regdata;
}

void setreg(int i, u32 val)
{
    volatile u32 mem = 0;
    mem = readmem(regs[i].addr);
    DEBUG_PRINT("Old contents: 0x%08x\n", mem);
    mem &= ~(regs[i].mask << regs[i].shift);
    DEBUG_PRINT("Unmasked contents: 0x%08x\n", mem);
    DEBUG_PRINT("unmasked val: 0x%08x\n", val);
    val &= regs[i].mask;
    DEBUG_PRINT("mask: 0x%08x\n", regs[i].mask);
    DEBUG_PRINT("masked val: 0x%08x\n", val);
    mem |= val << regs[i].shift;
    DEBUG_PRINT("Embedded value: 0x%08x\n", mem);
    writemem(regs[i].addr, mem);
}
