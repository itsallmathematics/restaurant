#ifndef STANDARD_H
    #define STANDARD_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <assert.h>
    #ifdef DEBUG
        #define D if(1) 
        #else
        #define D if(0) 
    #endif
    
    #define ONE_NIBBLE 4
    #define ONE_BYTE 8
    #define TWO_BYTES 16
    #define THREE_BYTES 24
    #define FOUR_BYTES 32
    #define FIVE_BYTES 40
    #define SIX_BYTES 48
    #define SEVEN_BYTES 56
    #define EIGHT_BYTES 64

    #define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c"
    #define BYTE_TO_BINARY(byte)  \
        (byte & (1<<7) ? '1' : '0'), \
        (byte & (1<<6) ? '1' : '0'), \
        (byte & (1<<5) ? '1' : '0'), \
        (byte & (1<<4) ? '1' : '0'), \
        ' ', \
        (byte & (1<<3) ? '1' : '0'), \
        (byte & (1<<2) ? '1' : '0'), \
        (byte & (1<<1) ? '1' : '0'), \
        (byte & (1<<0) ? '1' : '0') // <<0 isn't necessary, but just demonstrates the idea

    #define PS(x) printf("%s\n", x)
    #define PI(x) printf("%d\n", x)
    #define PUM(msg, x) printf("%s %u\n", msg, x)
    #define ERR(msg) fprintf(stderr, "%s\n", msg)
    #define PU(x) printf("%u\n", x)
    #define PUL(x) printf("%lu\n", x)
    #define RES return EXIT_SUCCESS
    #define REF return EXIT_FAILURE
    #define IFN(x) if(NULL == x)
    #define PP(x) printf("%p\n", x)
    #define PPM(msg, x) printf("%s %p\n", msg, x)
    #define MAIN_V int main(void)
    #define MAIN_A int main(int argc, char **argv)
    typedef char* CS;


#endif
