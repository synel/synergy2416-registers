/* This is the modem control program written for the synergy2416 board
 *
 *  Chao Ling <chaol@timeamerica.com>
 *
 * To turn on the gprs module, pull down GPA25 for more than 1 second 
 ****************************************************
 */

#include <unistd.h>
#include <syslog.h>
#include "s3cregisters.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)   fprintf(stderr, fmt, ## args) 
#else
#define DEBUG_PRINT(fmt, args...)    /* Don't print in release builds */
#endif

enum REGSET
{
    lcdctl = 0,
    ledctl_green,
    ledctl_red,
    modemctl,	
    lcddata,
    leddata_green,
    leddata_red,
    modemdata, 
};

void printusage()
{
	printf("============= LED control command ===================\n");
	printf("============= synctl [red|green] [on|off] ======\n");
        printf("============= GPRS control command ===================\n");
        printf("============= synctl [gprs] [on|off] ======\n");
        printf("============= LCD control command ===================\n");
        printf("============= synctl [lcd] [on|off] ======\n");
        printf("============= synctl [printreg] [regAddr] [shift] [mask] ======\n");
        printf("============= synctl [writereg] [regAddr] [value] ======\n");
}

u32 printregs(u32 addr, u32 shift, u32 mask) {
	volatile u32 mem = 0;
    	u32 regdata = 0;
    	mem = readmem(addr);
    	DEBUG_PRINT("Read Old contents: 0x%08x\n", mem);
    	regdata = (mem >> shift) & mask;
    	DEBUG_PRINT("Read Masked contents: 0x%08x\n", regdata);
    	return regdata;
}

void writeregs(u32 addr, u32 value) {
	volatile u32 mem = 0;
    	u32 regdata = 0;
    	mem = readmem(addr);
    	DEBUG_PRINT("Read Old contents: 0x%08x\n", mem);
	writemem(addr,value);
    	mem = readmem(addr);
    	DEBUG_PRINT("Read New contents: 0x%08x\n", mem);
}

int main(int argc, char *argv[])
{
    if (argc >= 3) {
        if (0 == strcmp("red", argv[1]))  {
		setreg(ledctl_red, 0);
		setreg(leddata_red, strcmp("off", argv[2])?1:0);
    	}
	else if (0 == strcmp("green", argv[1])) {
		setreg(ledctl_green,0);
		setreg(leddata_green, strcmp("off",argv[2])?1:0);
	}
	else if (0 == strcmp("gprs", argv[1])) {
		unsigned int waittime = 2; //sleep 2 seconds
		setreg(modemctl,0);
		setreg(modemdata, strcmp("off", argv[2])?1:0);	
		sleep(waittime);
		setreg(modemdata, strcmp("off", argv[2])?0:1);
	}
	else if (0 == strcmp("lcd", argv[1])) {
		setreg(lcdctl,0);
		setreg(lcddata, strcmp("off", argv[2])?0:1);	
	}
	else if (0 == strcmp("printreg", argv[1])) {
		u32 regaddr = 0;
		u32 shift = 0;
		u32 mask = 0x1;
		regaddr = strtoul(argv[2], NULL,16);
		if (NULL != argv[3]){
			shift = strtoul(argv[3], NULL,16);
		}
		if (NULL != argv[4]){
			mask = strtoul(argv[4], NULL,16);
		}
		printregs(regaddr,shift,mask);
	}
	else if (0 == strcmp("writereg", argv[1])) {
		u32 regaddr = 0;
		u32 value = 0;
		regaddr = strtoul(argv[2], NULL,16);
		if (NULL != argv[3]){
			value = strtoul(argv[3], NULL,16);
		}
		writeregs(regaddr,value);
	}
    } else {
	printusage();
	return -1;
    }
    return 0;
}
