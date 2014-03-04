#ifndef S3CREGISTERS_H
#define S3CREGISTERS_H
/*
 * Library functions to read and write the S3C2416 registers
 *
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

typedef unsigned int u32;
typedef unsigned long long u64;

/* Function to read mem mapped content by 32bit addr
 * @ parameter: 32bit memory address unsigned int
 * @ return: memory content as 32bit unsigned int
 * @ notes: none
 */

//static u32 readmem(u32 addr);

/* Function to write to mem mapped 32 bit addr
 * @ parameter: 32bit memory address unsigned int
 * @ parameter: 32bit value unsigned int
 * @ return: none
 * @ notes: none
 */

//static void writemem(u32 addr, u32 val);

/* Function to read s3c register value by name
 * @ parameter: register name
 * @ parameter: 32bit register value unsigned int
 * @ return: success or not
 * @ notes: none
 */

/*extern int readregbyname(const char *name, volatile u32* val); */

/* Function to read s3c register value by index
 * @ parameter: register index in the struct array
 * @ return: 32bit register value unsigned int
 * @ notes: none
 */

extern u32 readreg(int i);

/* Function to set s3c register value by name
 * @ parameter: register name
 * @ parameter: 32bit register value unsigned int
 * @ return: success or not
 * @ notes: none
 */


/* extern int setregbyname(const char *name, u32 val); */

/* Function to set s3c register value by index
 * @ parameter: register index in the struct array
 * @ parameter: 32bit register value unsigned int
 * @ return: none
 * @ notes: none
 */

extern void setreg(int i, u32 val);

#endif //S3CREGISTERS_H
