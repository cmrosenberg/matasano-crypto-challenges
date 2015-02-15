#include "hex2base64.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_base64letter()
{
    char i;

    fprintf(stderr, "Testing base64letter():\n");

    for(i = 0; i < 26; i++){
        assert(base64letter(i) == 'A'+i);
        fprintf(stderr, "%d -> %c \n", i, base64letter(i));
    }
    fprintf(stderr, "\n");

    for(i = 26; i < 52; i++){
      assert(base64letter(i) == ('a' + (i - 26)));
      fprintf(stderr, "%d -> %c \n", i, base64letter(i));
    }
    fprintf(stderr, "\n");

    for(i = 52; i < 62; i++){
        assert(base64letter(i) == '0'+(i - 52));
      fprintf(stderr, "%d -> %c \n", i, base64letter(i));
    }
    fprintf(stderr, "\n");

    assert(base64letter(62) == '+');
    fprintf(stderr, "62 -> %c \n", base64letter(62));
    fprintf(stderr, "\n");

    assert(base64letter(63) == '/');
    fprintf(stderr, "63 -> %c \n", base64letter(63));
    fprintf(stderr, "\n");
}

void test_determine_buffersize()
{
    assert(determine_buffersize(96) == 64+1);
}

void test_nibbles2byte()
{
    assert(nibbles2byte(0x3, 0x3) == 0x33);
    assert(nibbles2byte(0xf, 0xf) == 0xff);
}

void test_hex2nibble()
{
    assert(hex2nibble('0') == 0x0);
    assert(hex2nibble('1') == 0x1);
    assert(hex2nibble('5') == 0x5);
    assert(hex2nibble('a') == 0xa);
    assert(hex2nibble('A') == 0xA);
    assert(hex2nibble('F') == 0xF);
}

void test_convert_triplet()
{
    char buff[4];
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = 0;
    buff[3] = 0;

    convert_triplet(0x49, 0x27, 0x6d, buff);
    assert(buff[0] == 'S');
    printf("%c\n", buff[0]);
    assert(buff[1] == 'S');
    printf("%c\n", buff[1]);
    assert(buff[2] == 'd');
    printf("%c\n", buff[2]);
    assert(buff[3] == 't');
    printf("%c\n", buff[3]);
}

int main(void)
{
    test_base64letter();
    test_determine_buffersize();
    test_hex2nibble();
    test_nibbles2byte();
    test_convert_triplet();
    return 0;
}
