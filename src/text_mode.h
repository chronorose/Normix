#ifndef __NORMIX_TEXT_MODE__
#define __NORMIX_TEXT_MODE__

#include "stdlib.h"

void print(char ch);
void fprint(char* fmt, ...);
void error(char* err);
void printgl(int x, int y, char ch, char fg, char bg);
void printc(char ch, char fg, char bg);
void scroll();
void vga_print_char(char symbol);
void vga_print_str(char* str);
void vga_clear_screen();
void vga_print_uhex(unsigned int num);
void vga_print_udec(unsigned int num);
void vga_print_float(float num, int precision);

#endif
