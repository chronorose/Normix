void kmemmove(void* dest, const void* src, int count) {
    char* d = dest;
    const char* s = src;
    while (count) {
        *d++ = *s++;
        count--;
    }
}
