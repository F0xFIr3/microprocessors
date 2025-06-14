#include <8051.h>

void lcd_init() {
    P0 = 0x38; P2 = 0x1; P2 = 0x0;
    P0 = 0x0C; P2 = 0x1; P2 = 0x0;
    P0 = 0x01; P2 = 0x1; P2 = 0x0;
}


void lcd_set_cursor(unsigned char pos) {
    P0 = 0x80 | pos;
    P2 = 0x1; P2 = 0x0;
}


void lcd_display_char(unsigned char ch) {
    P0 = ch;
    P2 = 0x3; P2 = 0x2;
}


void lcd_clear() {
    P0 = 0x01;  
    P2 = 0x1; P2 = 0x0;
}


void lcd_display_str(unsigned char *str) {
    lcd_set_cursor(0);  
    while (*str != '\0' && str - str < 10) {  
        lcd_display_char(*str);
        str++;
    }
}


void lcd_display_operator(unsigned char operator) {
    unsigned char op_str[2];
    op_str[0] = operator;
    op_str[1] = '\0';
    lcd_display_str(op_str);
}


unsigned long atol_custom(unsigned char *str) {
    unsigned long res = 0;
    while (*str >= '0' && *str <= '9') {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}


void itoa_custom(unsigned long num, unsigned char *str) {
    unsigned char temp[10];
    unsigned char i = 0, j;
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (num > 0) {
        temp[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (j = 0; j < i; j++) {
        str[j] = temp[i - j - 1];
    }
    str[i] = '\0';
}


unsigned long calculate(unsigned long num1, unsigned long num2, unsigned char operator) {
    unsigned long result = 0;
    switch (operator) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/':
            if (num2 != 0) result = num1 / num2;
            else result = 0;
            break;
    }
    return result;
}


void main() {
	unsigned char result_ready = 0;
    unsigned char i, j, key;
    unsigned char number[11] = {0};  
    unsigned char num_index = 0;
    unsigned char *keys[16] = {
        "C", "0", "=", "/",
        "1", "2", "3", "*",
        "4", "5", "6", "-",
        "7", "8", "9", "+"
    };
    unsigned char row[5] = {0xFE, 0xFD, 0xFB, 0xF7};
    unsigned char col[5] = {0x1E, 0x1D, 0x1B, 0x17};
    unsigned long num1 = 0, num2 = 0, result = 0;
    unsigned char operator = 0;
	unsigned long d;

    lcd_init();

    while (1) {
        for (i = 0; i < 4; i++) {
            P3 = col[i];
            for (j = 0; j < 4; j++) {
                if (P1 == row[j]) {
                    key = *keys[i + j * 4];

                    switch (key) {
                        case '+': case '-': case '*': case '/':
    						if (num_index > 0 || result_ready) {
        						if (!result_ready)
            						num1 = atol_custom(number);
        						operator = key;
        						num_index = 0;
        						number[0] = '\0';
        						lcd_clear();
        						lcd_display_operator(operator);
        						result_ready = 0;
    							}
    					break;

         	            case '=':
    						if ((num_index > 0 || result_ready) && operator != 0) {
        						num2 = atol_custom(number);
        						result = calculate(num1, num2, operator);
        						itoa_custom(result, number);
        						lcd_clear();
        						lcd_display_str(number);
        						num1 = result;
        						num_index = 0;
        						result_ready = 1;
    						}
    					break;


                        case 'C':
    						num_index = 0;
    						number[0] = '\0';
    						num1 = 0;
    						num2 = 0;
    						operator = 0;
    						result_ready = 0;
    						lcd_clear();
    					break;

						default:
							if (result_ready) {
        						num_index = 0;
        						number[0] = '\0';
        						result_ready = 0;
    						}
    						if (num_index < 10) {
        						number[num_index++] = key;
        						number[num_index] = '\0';
        						lcd_clear();
        						lcd_display_str(number);
    						} else {
        						lcd_clear();
        						lcd_display_str("Too long");
        						num_index = 0;
        						number[0] = '\0';
    						}
                        	break;
                    }

                    for (d = 0; d < 5000; d++);
                }
            }
        }
    }
}
