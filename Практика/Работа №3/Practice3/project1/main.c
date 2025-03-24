#include <8051.h>
void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 5; j++);
}

void send_cmd(unsigned char cmd) {
    P0 = cmd;  
    P2 = 0x00; 
    P2 = 0x01; 
    delay(1);
    P2 = 0x00; 
}

void send_data(unsigned char *dat) {
    P0 = dat;  
    P2 = 0x02; 
    P2 = 0x03; 
    delay(1);
    P2 = 0x02; 
}
void vyvod(unsigned char *text){
	unsigned char i, j, len = 0;
	unsigned char *probel=" ";
	send_cmd(0xC0);
    while (text[len] != '\0') len++; 
    for (i = 0; i < len; i++) {
         send_data(text[i]);
		 send_data(probel);
	}
}
void scroll_text(unsigned char *text) {
    unsigned char i, j, len = 0, temp = 0,cursor_pos = 0;;
    while (text[len] != '\0') len++;
	temp =len;
    while (1) {
        for (i = 0; i < len+20; i++) {
			send_cmd(0x80);
            for (j = 0; j < 20; j++) { 
                if (i + j < 20) 
                    send_data(' '); 
                else if (i + j - 20 < len) 
                    send_data(text[(i + j - 20)%len]); 
				else 
                    send_data(' ');
			}
			send_cmd(0xC0 + ((i - 20 + len) % 20));

            delay(3);
        }
    }
}


void main()
{ 
	unsigned char first[] = {0xAC, 0xA9, 0xB2, 0xC0, 0xAE, 0xB2, 0xAB, 0xA9,0xAA, 0x00};
	unsigned char second[] = {0xB0, 0xA0, 0xA2, 0xA5, 0xAC, 0x00};
	vyvod(second);
	scroll_text(first);
	while(1);
}