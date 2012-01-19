#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "blake512.h"

// These tests are copied from the original blake512_light.c.
int runtests512() {
    int i, v, e;
    uint8_t data[144], digest[64];
    uint8_t test1[]= {0x97, 0x96, 0x15, 0x87, 0xF6, 0xD9, 0x70, 0xFA, 0xBA, 0x6D, 0x24, 0x78, 0x04, 0x5D, 0xE6, 0xD1,
           0xFA, 0xBD, 0x09, 0xB6, 0x1A, 0xE5, 0x09, 0x32, 0x05, 0x4D, 0x52, 0xBC, 0x29, 0xD3, 0x1B, 0xE4,
           0xFF, 0x91, 0x02, 0xB9, 0xF6, 0x9E, 0x2B, 0xBD, 0xB8, 0x3B, 0xE1, 0x3D, 0x4B, 0x9C, 0x06, 0x09,
           0x1E, 0x5F, 0xA0, 0xB4, 0x8B, 0xD0, 0x81, 0xB6, 0x34, 0x05, 0x8B, 0xE0, 0xEC, 0x49, 0xBE, 0xB3};
    uint8_t test2[]= {0x31, 0x37, 0x17, 0xD6, 0x08, 0xE9, 0xCF, 0x75, 0x8D, 0xCB, 0x1E, 0xB0, 0xF0, 0xC3, 0xCF, 0x9F,
           0xC1, 0x50, 0xB2, 0xD5, 0x00, 0xFB, 0x33, 0xF5, 0x1C, 0x52, 0xAF, 0xC9, 0x9D, 0x35, 0x8A, 0x2F,
           0x13, 0x74, 0xB8, 0xA3, 0x8B, 0xBA, 0x79, 0x74, 0xE7, 0xF6, 0xEF, 0x79, 0xCA, 0xB1, 0x6F, 0x22,
           0xCE, 0x1E, 0x64, 0x9D, 0x6E, 0x01, 0xAD, 0x95, 0x89, 0xC2, 0x13, 0x04, 0x5D, 0x54, 0x5D, 0xDE};

    for(i = 0; i < 144; ++i) data[i] = 0;

    blake512_hash(digest, data, 1);
    v = 0; e = 0;
    for(i = 0; i < 64; ++i) {
        printf("%02X", digest[i]);
        if (digest[i] != test1[i]) v = 1;
    }
    if (v) { printf("\nerror\n"); e++; }
    else printf("\nok\n");

    for(i = 0; i < 144; ++i) data[i] = 0;

    blake512_hash(digest, data, 144);
    v = 0;
    for(i = 0; i < 64; ++i) {
        printf("%02X", digest[i]);
        if (digest[i] != test2[i]) v = 1;
    }
    if (v) { printf("\nerror\n"); e++; }
    else printf("\nok\n");

    return e;
}

// These tests are copied from the original blake384_light.c.
int runtests384() {
    int i, v, e;
    uint8_t data[144], digest[64];
    uint8_t test1[]= {0x10, 0x28, 0x1F, 0x67, 0xE1, 0x35, 0xE9, 0x0A, 0xE8, 0xE8, 0x82, 0x25, 0x1A, 0x35, 0x55, 0x10, 
           0xA7, 0x19, 0x36, 0x7A, 0xD7, 0x02, 0x27, 0xB1, 0x37, 0x34, 0x3E, 0x1B, 0xC1, 0x22, 0x01, 0x5C, 
           0x29, 0x39, 0x1E, 0x85, 0x45, 0xB5, 0x27, 0x2D, 0x13, 0xA7, 0xC2, 0x87, 0x9D, 0xA3, 0xD8, 0x07};
    uint8_t test2[]= {0x0B, 0x98, 0x45, 0xDD, 0x42, 0x95, 0x66, 0xCD, 0xAB, 0x77, 0x2B, 0xA1, 0x95, 0xD2, 0x71, 0xEF, 
           0xFE, 0x2D, 0x02, 0x11, 0xF1, 0x69, 0x91, 0xD7, 0x66, 0xBA, 0x74, 0x94, 0x47, 0xC5, 0xCD, 0xE5, 
           0x69, 0x78, 0x0B, 0x2D, 0xAA, 0x66, 0xC4, 0xB2, 0x24, 0xA2, 0xEC, 0x2E, 0x5D, 0x09, 0x17, 0x4C}; 

    for (i = 0; i < 144; ++i) data[i] = 0;  

    blake384_hash(digest, data, 1);    
    v = 0;
    for (i = 0; i < 48; ++i) {
        printf("%02X", digest[i]);
        if (digest[i] != test1[i]) v = 1;
    }
    if (v) { printf("\nerror\n"); e++; }
    else printf("\nok\n");

    for (i = 0; i < 144; ++i) data[i] = 0;  

    blake384_hash(digest, data, 144);    
    v = 0;
    for (i = 0; i < 48; ++i) {
        printf("%02X", digest[i]);
        if (digest[i] != test2[i]) v = 1;
    }
    if (v) { printf("\nerror\n"); e++; }
    else printf("\nok\n");

    return e;
}

int hash_main(int argc, char **argv) {
    uint8_t digest[64], buf[1024];
    size_t c, i;

    state S;
    blake512_init(&S);
    while (!feof(stdin)) {
        c = fread(buf, 1, 1024, stdin);
        blake512_update(&S, buf, c * 8);
    }
    blake512_final(&S, digest);

    for(i = 0; i < 64; ++i) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}

int hmac_main(int argc, char **argv) {
    uint8_t digest[64], buf[1024];
    size_t c, i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <key>\n", argv[0]);
        return 1;
    }

    hmac_state S;
    hmac_blake512_init(&S, (uint8_t *) argv[1], strlen(argv[1]));
    while (!feof(stdin)) {
        c = fread(buf, 1, 1024, stdin);
        hmac_blake512_update(&S, buf, c * 8);
    }
    hmac_blake512_final(&S, digest);

    for(i = 0; i < 64; ++i) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}

int main(int argc, char **argv) {
    //return runtests512();
    //return runtests384();
    //return hash_main(argc, argv);
    return hmac_main(argc, argv);
}
