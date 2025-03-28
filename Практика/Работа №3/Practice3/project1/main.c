#include <8051.h>
void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 5; j++);
}

void send_cmd(unsigned char cmd) {
    P0 = cmd;   
    P2 = 0x01;
    P2 = 0x00; 
}

void send_data(unsigned char *dat) {
    P0 = dat;  
    P2 = 0x03; 
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
void scroll_text(unsigned char *text, unsigned int pos) {
    unsigned char len = 0;
	unsigned int  i,j,k;
    while (text[len] != '\0') len++;
	while(1) {
  		j = 0;
  		while (j != 20) {
   			if (j < len) {
    			send_cmd(pos);
    			for (i = 0; i < j+1; i++) {
     				send_data(text[i]);
    			}
   			}
   			else {
    			send_cmd(pos);
    			for (i = 0; i < len; i++) {
     				send_data(text[i]);
    			}
    			send_data(" ");
   			}
   			pos -= 1;
   			j += 1;
  		}
  		k = len;
  		while (k != -1) {
   			send_cmd(0x80);
   			for (i = len-k; i < len; i++) {
    			send_data(text[i]); 
   			}
   			send_data(" ");
   			k -= 1;
  		}
  		pos = 0x93;
 	}
}



void main()
{ 
	unsigned char first[] = {0xAC, 0xA9, 0xB2, 0xC0, 0xAE, 0xB2, 0xAB, 0xA9,0xAA, 0x00};
	unsigned char second[] = {0xB0, 0xA0, 0xA2, 0xA5, 0xAC, 0x00};
	unsigned int pos = 0x93;
	vyvod(second);
	scroll_text(first, pos);
	while(1);
}