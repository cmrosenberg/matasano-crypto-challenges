char base64letter(char byte);

unsigned char hex2nibble(char hex_letter);

unsigned char nibbles2byte(char greatest, char smallest);

unsigned int determine_buffersize(unsigned int hexbuff_len);

void convert_triplet(const unsigned char a, const unsigned char b,
        const unsigned char c, char * buff);

void hex2base64(void);
