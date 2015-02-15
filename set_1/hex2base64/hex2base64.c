#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define LOWEST_SIX_BYTES_SET 63
#define LOWEST_FOUR_BYTES_SET 15
#define LOWEST_TWO_BYTES_SET 3

#define INPUT_BUFF_SIZE 1024

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

void convert_triplet(const unsigned char a, const unsigned char b,
        const unsigned char c, char * buff)
{
    char helper;

    buff[0] = base64letter(a >> 2);

    helper = (a & LOWEST_TWO_BYTES_SET) << 4;
    buff[1] = base64letter(helper | (b >> 4));

    helper = ((b & LOWEST_FOUR_BYTES_SET) << 2);
    buff[2] = base64letter(helper | (c >> 6));

    buff[3] = base64letter(c & LOWEST_SIX_BYTES_SET);
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
    /* test_base64letter(); */
    /* test_determine_buffersize(); */
    /* test_hex2nibble(); */
    /* test_nibbles2byte(); */
    /* test_convert_triplet(); */

    char input_buff[INPUT_BUFF_SIZE];
    char * output_buff;
    unsigned int input_strlen, output_bufflen, i,j, k, groups_of_three,
                 remainder = 0;


    scanf("%s", input_buff);

    input_strlen = strnlen(input_buff, INPUT_BUFF_SIZE);
    output_bufflen = determine_buffersize(input_strlen);

    output_buff = malloc(output_bufflen);

    groups_of_three = input_strlen / 6;
    remainder = input_strlen % 6;

    for(i = 0, j = 0, k = 0; i < groups_of_three; i++, j = i*6, k += 4){
        convert_triplet(nibbles2byte(hex2nibble(input_buff[j]),
                    hex2nibble(input_buff[j+1])),
                nibbles2byte(hex2nibble(input_buff[j+2]),
                    hex2nibble(input_buff[j+3])),
                nibbles2byte(hex2nibble(input_buff[j+4]),
                    hex2nibble(input_buff[j+5])),
                &(output_buff[k]));
    }

    if(remainder == 4){
        convert_triplet(nibbles2byte(hex2nibble(input_buff[j]),
                    hex2nibble(input_buff[j+1])),
                nibbles2byte(hex2nibble(input_buff[j+2]),
                    hex2nibble(input_buff[j+3])),
                0, &(output_buff[k]));
        output_buff[output_bufflen-2] = '=';
    } else if(remainder == 2) {
        convert_triplet(nibbles2byte(hex2nibble(input_buff[j]),
                    hex2nibble(input_buff[j+1])),
                0, 0, &(output_buff[k]));
        output_buff[output_bufflen-3] = '=';
        output_buff[output_bufflen-2] = '=';
    }


    output_buff[output_bufflen-1] = 0;
    puts(output_buff);
    free(output_buff);
    return 0;
}
