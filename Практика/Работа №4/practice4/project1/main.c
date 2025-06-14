#include <8051.h>
void msec (int x) {
	while(x-->0){
		TH0 = -(1000)>>8;
		TL0=-1000; 
		TR0=1; 
		do;
		while(TF0==1); 
		TF0=0;
		TR0=0;
	}
}
void main() 
{
	int i;
	unsigned char array[5];
	TMOD=0x1; 
	array[0] = 0x0; 
	array[1] = 0x48;
	array[2] = 0x7;
	array[3] = 0x30;
	array[4] = 0x80;
	while(1) {
		P1=array[0];
		msec(100);
		P1=array[1];
		msec(100);
		P1=array[2];
		msec(100);
		P1=array[3];
		msec(300);
		P1=array[4];
		msec(500);
	}	
}