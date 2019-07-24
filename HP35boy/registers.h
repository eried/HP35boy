//registri cpu
unsigned char a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char d[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char e[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char f[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char t[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit temporary
unsigned char s[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //12 bit Status da S0 a S11
unsigned char p = 0;
unsigned char pc = 0;
unsigned char offset = 0;
unsigned char ret = 0;
unsigned char temp;
unsigned char first;
unsigned char last;
unsigned char zero = 0;
unsigned char carry = 0;
unsigned char prevCarry = 0;
unsigned char fetch_h;
unsigned char fetch_l;
unsigned char ROM = 0;
unsigned char op_code = 0;
unsigned char word_select = 0;
unsigned char key_code = -1;
unsigned char key_rom = 0;
unsigned char display_status = 0;
unsigned char error = 0;
unsigned char chr_prtd = 0;
