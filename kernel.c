void kernel_entry(void) {
    *((short int*) 0xB8000) = 0;
    for(;;) ;
}
