
CDEF=  -UNO_SLEEP                      # Use the usleep function
CDEFS=  $(CDEF) 

COPTS=  -O3 -Wall -I.

CFLAGS= $(COPTS) $(CDEFS)
 
.PHONY: all
all: synctl
.PHONY: clean
clean:
	rm -f synctl synctl.o s3cregisters.o
synctl: synctl.o s3cregisters.o
	$(CC) $(CFLAGS) -o $@ synctl.o s3cregisters.o
synctl.o: synctl.c s3cregisters.h
	$(CC)  $(CFLAGS) -c synctl.c
s3cregisters.o: s3cregisters.c s3cregisters.h
	$(CC)  $(CFLAGS) -c s3cregisters.c

