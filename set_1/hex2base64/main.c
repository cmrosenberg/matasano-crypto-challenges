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


void test_base64letter(){

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

int main(void)
{
    test_base64letter();
    return 0;
}
