
CDEF=  -UNO_SLEEP                      # Use the usleep function
CDEFS=  $(CDEF) 

COPTS=  -O3 -Wall -I.

CFLAGS= $(COPTS) $(CDEFS)
 
.PHONY: all
all: ledcontroller
.PHONY: clean
clean:
	rm -f ledcontroller ledcontroller.o s3cregisters.o
ledcontroller: ledcontroller.o s3cregisters.o
	$(CC) $(CFLAGS) -o $@ ledcontroller.o s3cregisters.o
ledcontroller.o: ledcontroller.c s3cregisters.h
	$(CC)  $(CFLAGS) -c ledcontroller.c
s3cregisters.o: s3cregisters.c s3cregisters.h
	$(CC)  $(CFLAGS) -c s3cregisters.c

