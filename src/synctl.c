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

#undef DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    DEBUG_PRINT(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)    /* Don't print in release builds */
#endif

enum REGSET
{
    ledctl_green = 0,
    ledctl_red,
    modemctl,	
    leddata_green,
    leddata_red,
    modemdata 
};

void printusage()
{
	printf("============= LED control command ===================\n");
	printf("============= synctl [red|green] [on|off] ======\n");
        printf("============= GPRS control command ===================\n");
        printf("============= synctl [gprs] [on|off] ======\n");
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
    } else {
	printusage();
	return -1;
    }
    return 0;
}
