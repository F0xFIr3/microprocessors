#include <8051.h>
void main() {
	int i;
	char xdata *ptr;
	char test, nabor;
	P1 = 0x0;
	nabor = 0xAA;
	ptr = (char xdata *) 0x680;
	for (i = 0; i<1024; i++) {
		*ptr = nabor;
		test = *ptr;
		if (test != nabor) {
			P1=0x1;
			break;
		}
		ptr++;
	}
}
