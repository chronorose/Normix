#ifndef __NORMIX_STDLIB__
#define __NORMIX_STDLIB__

#define SWAP(x, y, T) do { T temp = x; x = y; y = temp; } while(0);

extern float sqrt(float arg);
extern float cos(float arg);
extern float sin(float arg);

#define PI 3.14159265358979323846
#define PI_2 1.57079632679489661923

void kmemmove(void* dest, const void* src, int count);
int max(int a1, int a2);
void kmemset(void* s, int c, unsigned int n);

#endif
