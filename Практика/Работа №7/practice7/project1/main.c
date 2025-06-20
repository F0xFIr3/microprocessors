#include <8051.h>
	

int T = 20; //ms
int Q; //%
int t;
int Qmin = 30;//%
int Qmax = 60;//%


//R = 45536(0x B1E0)
void square(){
	t = Q*133/10;
	P01 = 1;
	while(t>0){
		t--;
		}
	P01 = 0;
	while(TF2 == 0);
	TF2 = 0;
	}

void main(){
	int flag = 0;
	Q=60;
	RCAP2H = 0xB1;
	RCAP2L = 0xE0;
	TH2 = 0xFF;
	TL2 = 0xFF;
	ET2 = 1;
	EA = 1;
	T2CON = 0b100;
	while(1){
	if(P11 == 1 && flag ==0){
		Q -= 10;
		flag = 1;
	}
	
	if(P00 == 1 && flag == 0){
		Q += 10;
	flag = 1;
	}
	if(P00 == 0 && flag == 1 && P11 == 0) flag = 0;
		square();	
	}

}
