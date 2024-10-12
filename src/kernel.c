extern void sayhi(void);

void kernel_entry() {
    sayhi();
    /**((short int*) 0xB8000) = 0;*/
    for(;;);
}
