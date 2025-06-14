#include <8051.h>
void tput(unsigned char c1)
{
	SBUF=c1;
	while(!TI); 
	TI=0; 
}
void init_serial()
{
	PCON_BITS.B7 = 0; 
  	TMOD_BITS.B6 = 0; 
  	TMOD_BITS.B4 = 0; 
  	TMOD_BITS.B5 = 1;
  	TH1 = 0x0FD;  
  	TR1 = 1; 
	SCON = 0;
	SCON_BITS.B3 = 1;
  	SCON_BITS.B4 = 0;  
  	SCON_BITS.B5 = 0; 
  	SCON_BITS.B6 = 1; 
  	SCON_BITS.B7 = 1; 
}
void main()
{
	int i;
	char xdata *ptr;
	ptr = (char xdata *) 0x50;
    ptr[0] = 'L';
    ptr[1] = 'i';
    ptr[2] = 's';
    ptr[3] = 'y';
    ptr[4] = 'a';
    ptr[5] = 'n';
    ptr[6] = 's';
    ptr[7] = 'k';
    ptr[8] = 'i';
    ptr[9] = 'y';
	init_serial();
	while(1){
		for(i=0; i<10; i++)
		{
			tput(ptr[i]);
		}
	}
}