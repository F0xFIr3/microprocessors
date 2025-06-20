#include <8051.h>

void main()
{
int i;
P0 = 0;
while(1){
for(i = 0; i<64;i++){
	P0 = 0;
	}
 for(i = 64; i<128;i++){
	P0 = 255 ;
	}
for(i = 128; i<193;i++){
	P0 = i;
	}
for(i = 193;i>64;i-=2){
	P0 = i;
	}
for(i = 0; i<64;i++){
	P0 = 0;
	}
}
}
