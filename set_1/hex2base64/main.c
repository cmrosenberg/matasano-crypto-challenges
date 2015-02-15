#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define LOWEST_SIX_BYTES_SET 63

char base64letter(char byte)
{
    assert(byte <= LOWEST_SIX_BYTES_SET);

    if(byte <= 25){
        return 'A'+ byte;
    }

    if(byte >= 26 && byte <= 51){
        return 'a'+ (byte-26);
    }

    if(byte >= 51 && byte <= 61){
        return '0' + (byte - 52);
    }

    if(byte == 62){
        return '+';
    }

    return '/';
}

unsigned char hex2nibble(char hex_letter)
{

    assert(hex_letter <= 'f');

    if(hex_letter >= '0' && hex_letter <=  '9'){
        return hex_letter - '0';
    }

    if(hex_letter >= 'A' && hex_letter <= 'F')
    {
        return hex_letter - 'A' + 10;
    }

    return hex_letter - 'a' + 10;
}

unsigned char nibbles2byte(char greatest, char smallest)
{
    char result = 0;
    result = greatest << 4;
    result = result | smallest;

    return result;
}

unsigned int determine_buffersize(unsigned int hexbuff_len)
{
    /* We assume that the hex strings we deal with
     * are of even length -ie. that they correspond
     * to bytes (two hexadecimal letters designate a byte)
     * and not arbitrary numbers */
    assert(hexbuff_len % 2 == 0);

    unsigned int groups_of_six = hexbuff_len / 6;
    unsigned int remainder = hexbuff_len % 6;

    /* We add one because the buffer must contain
     * the string-terminating '0' */
    return (groups_of_six * 4) + (remainder / 2) + 1;
}

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

int main(void)
{
    test_base64letter();
    test_determine_buffersize();
    test_hex2nibble();
    test_nibbles2byte();
    return 0;
}
