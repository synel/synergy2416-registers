/* This is the led control program written for the synergy2416 board
 *
 *  Chao Ling <chaol@timeamerica.com>
 *
 * Pin 15 RED LED 
 * Pin 16 GREEN LED
 * 1 --> on
 * 0 --> off
 ****************************************************
 */


#include <syslog.h>
#include "s3cregisters.h"

#undef DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    DEBUG_PRINT(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)    /* Don't print in release builds */
#endif

enum LEDREGSET
{
    ledctl_green = 0,
    ledctl_red,
    leddata_green,
    leddata_red 
};

void printusage()
{
	printf("============= ledcontrol command ===================\n");
	printf("============= ledcontrol [red|green] [on|off] ======\n");
}

int main(int argc, char *argv[])
{
    if (argc >= 3) {
        if ( 0 == strcmp("red",argv[1]) ) {
		setreg(ledctl_red,0);
		setreg(leddata_red,strcmp("off",argv[2])?1:0);
    	}
	else {
		setreg(ledctl_green,0);
		setreg(leddata_green,strcmp("off",argv[2])?1:0);
	}	
    } else {
	printusage();
	return -1;
    }
    return 0;
}
