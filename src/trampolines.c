#include "trampolines.h"
#include "alloc.h"
#include "printer.h"
void kernel_panic(char *msg, int vector) {
    print(msg, vector);
    for (;;) ;
}
static void panic_handler(int vector) {
    kernel_panic("unhandled interrupt %x", vector);
}
static void trampoline_0x00() { panic_handler(0x00); }
static void trampoline_0x01() { panic_handler(0x01); }
static void trampoline_0x02() { panic_handler(0x02); }
static void trampoline_0x03() { panic_handler(0x03); }
static void trampoline_0x04() { panic_handler(0x04); }
static void trampoline_0x05() { panic_handler(0x05); }
static void trampoline_0x06() { panic_handler(0x06); }
static void trampoline_0x07() { panic_handler(0x07); }
static void trampoline_0x08() { panic_handler(0x08); }
static void trampoline_0x09() { panic_handler(0x09); }
static void trampoline_0x0a() { panic_handler(0x0a); }
static void trampoline_0x0b() { panic_handler(0x0b); }
static void trampoline_0x0c() { panic_handler(0x0c); }
static void trampoline_0x0d() { panic_handler(0x0d); }
static void trampoline_0x0e() { panic_handler(0x0e); }
static void trampoline_0x0f() { panic_handler(0x0f); }
static void trampoline_0x10() { panic_handler(0x10); }
static void trampoline_0x11() { panic_handler(0x11); }
static void trampoline_0x12() { panic_handler(0x12); }
static void trampoline_0x13() { panic_handler(0x13); }
static void trampoline_0x14() { panic_handler(0x14); }
static void trampoline_0x15() { panic_handler(0x15); }
static void trampoline_0x16() { panic_handler(0x16); }
static void trampoline_0x17() { panic_handler(0x17); }
static void trampoline_0x18() { panic_handler(0x18); }
static void trampoline_0x19() { panic_handler(0x19); }
static void trampoline_0x1a() { panic_handler(0x1a); }
static void trampoline_0x1b() { panic_handler(0x1b); }
static void trampoline_0x1c() { panic_handler(0x1c); }
static void trampoline_0x1d() { panic_handler(0x1d); }
static void trampoline_0x1e() { panic_handler(0x1e); }
static void trampoline_0x1f() { panic_handler(0x1f); }
static void trampoline_0x20() { panic_handler(0x20); }
static void trampoline_0x21() { panic_handler(0x21); }
static void trampoline_0x22() { panic_handler(0x22); }
static void trampoline_0x23() { panic_handler(0x23); }
static void trampoline_0x24() { panic_handler(0x24); }
static void trampoline_0x25() { panic_handler(0x25); }
static void trampoline_0x26() { panic_handler(0x26); }
static void trampoline_0x27() { panic_handler(0x27); }
static void trampoline_0x28() { panic_handler(0x28); }
static void trampoline_0x29() { panic_handler(0x29); }
static void trampoline_0x2a() { panic_handler(0x2a); }
static void trampoline_0x2b() { panic_handler(0x2b); }
static void trampoline_0x2c() { panic_handler(0x2c); }
static void trampoline_0x2d() { panic_handler(0x2d); }
static void trampoline_0x2e() { panic_handler(0x2e); }
static void trampoline_0x2f() { panic_handler(0x2f); }
static void trampoline_0x30() { panic_handler(0x30); }
static void trampoline_0x31() { panic_handler(0x31); }
static void trampoline_0x32() { panic_handler(0x32); }
static void trampoline_0x33() { panic_handler(0x33); }
static void trampoline_0x34() { panic_handler(0x34); }
static void trampoline_0x35() { panic_handler(0x35); }
static void trampoline_0x36() { panic_handler(0x36); }
static void trampoline_0x37() { panic_handler(0x37); }
static void trampoline_0x38() { panic_handler(0x38); }
static void trampoline_0x39() { panic_handler(0x39); }
static void trampoline_0x3a() { panic_handler(0x3a); }
static void trampoline_0x3b() { panic_handler(0x3b); }
static void trampoline_0x3c() { panic_handler(0x3c); }
static void trampoline_0x3d() { panic_handler(0x3d); }
static void trampoline_0x3e() { panic_handler(0x3e); }
static void trampoline_0x3f() { panic_handler(0x3f); }
static void trampoline_0x40() { panic_handler(0x40); }
static void trampoline_0x41() { panic_handler(0x41); }
static void trampoline_0x42() { panic_handler(0x42); }
static void trampoline_0x43() { panic_handler(0x43); }
static void trampoline_0x44() { panic_handler(0x44); }
static void trampoline_0x45() { panic_handler(0x45); }
static void trampoline_0x46() { panic_handler(0x46); }
static void trampoline_0x47() { panic_handler(0x47); }
static void trampoline_0x48() { panic_handler(0x48); }
static void trampoline_0x49() { panic_handler(0x49); }
static void trampoline_0x4a() { panic_handler(0x4a); }
static void trampoline_0x4b() { panic_handler(0x4b); }
static void trampoline_0x4c() { panic_handler(0x4c); }
static void trampoline_0x4d() { panic_handler(0x4d); }
static void trampoline_0x4e() { panic_handler(0x4e); }
static void trampoline_0x4f() { panic_handler(0x4f); }
static void trampoline_0x50() { panic_handler(0x50); }
static void trampoline_0x51() { panic_handler(0x51); }
static void trampoline_0x52() { panic_handler(0x52); }
static void trampoline_0x53() { panic_handler(0x53); }
static void trampoline_0x54() { panic_handler(0x54); }
static void trampoline_0x55() { panic_handler(0x55); }
static void trampoline_0x56() { panic_handler(0x56); }
static void trampoline_0x57() { panic_handler(0x57); }
static void trampoline_0x58() { panic_handler(0x58); }
static void trampoline_0x59() { panic_handler(0x59); }
static void trampoline_0x5a() { panic_handler(0x5a); }
static void trampoline_0x5b() { panic_handler(0x5b); }
static void trampoline_0x5c() { panic_handler(0x5c); }
static void trampoline_0x5d() { panic_handler(0x5d); }
static void trampoline_0x5e() { panic_handler(0x5e); }
static void trampoline_0x5f() { panic_handler(0x5f); }
static void trampoline_0x60() { panic_handler(0x60); }
static void trampoline_0x61() { panic_handler(0x61); }
static void trampoline_0x62() { panic_handler(0x62); }
static void trampoline_0x63() { panic_handler(0x63); }
static void trampoline_0x64() { panic_handler(0x64); }
static void trampoline_0x65() { panic_handler(0x65); }
static void trampoline_0x66() { panic_handler(0x66); }
static void trampoline_0x67() { panic_handler(0x67); }
static void trampoline_0x68() { panic_handler(0x68); }
static void trampoline_0x69() { panic_handler(0x69); }
static void trampoline_0x6a() { panic_handler(0x6a); }
static void trampoline_0x6b() { panic_handler(0x6b); }
static void trampoline_0x6c() { panic_handler(0x6c); }
static void trampoline_0x6d() { panic_handler(0x6d); }
static void trampoline_0x6e() { panic_handler(0x6e); }
static void trampoline_0x6f() { panic_handler(0x6f); }
static void trampoline_0x70() { panic_handler(0x70); }
static void trampoline_0x71() { panic_handler(0x71); }
static void trampoline_0x72() { panic_handler(0x72); }
static void trampoline_0x73() { panic_handler(0x73); }
static void trampoline_0x74() { panic_handler(0x74); }
static void trampoline_0x75() { panic_handler(0x75); }
static void trampoline_0x76() { panic_handler(0x76); }
static void trampoline_0x77() { panic_handler(0x77); }
static void trampoline_0x78() { panic_handler(0x78); }
static void trampoline_0x79() { panic_handler(0x79); }
static void trampoline_0x7a() { panic_handler(0x7a); }
static void trampoline_0x7b() { panic_handler(0x7b); }
static void trampoline_0x7c() { panic_handler(0x7c); }
static void trampoline_0x7d() { panic_handler(0x7d); }
static void trampoline_0x7e() { panic_handler(0x7e); }
static void trampoline_0x7f() { panic_handler(0x7f); }
static void trampoline_0x80() { panic_handler(0x80); }
static void trampoline_0x81() { panic_handler(0x81); }
static void trampoline_0x82() { panic_handler(0x82); }
static void trampoline_0x83() { panic_handler(0x83); }
static void trampoline_0x84() { panic_handler(0x84); }
static void trampoline_0x85() { panic_handler(0x85); }
static void trampoline_0x86() { panic_handler(0x86); }
static void trampoline_0x87() { panic_handler(0x87); }
static void trampoline_0x88() { panic_handler(0x88); }
static void trampoline_0x89() { panic_handler(0x89); }
static void trampoline_0x8a() { panic_handler(0x8a); }
static void trampoline_0x8b() { panic_handler(0x8b); }
static void trampoline_0x8c() { panic_handler(0x8c); }
static void trampoline_0x8d() { panic_handler(0x8d); }
static void trampoline_0x8e() { panic_handler(0x8e); }
static void trampoline_0x8f() { panic_handler(0x8f); }
static void trampoline_0x90() { panic_handler(0x90); }
static void trampoline_0x91() { panic_handler(0x91); }
static void trampoline_0x92() { panic_handler(0x92); }
static void trampoline_0x93() { panic_handler(0x93); }
static void trampoline_0x94() { panic_handler(0x94); }
static void trampoline_0x95() { panic_handler(0x95); }
static void trampoline_0x96() { panic_handler(0x96); }
static void trampoline_0x97() { panic_handler(0x97); }
static void trampoline_0x98() { panic_handler(0x98); }
static void trampoline_0x99() { panic_handler(0x99); }
static void trampoline_0x9a() { panic_handler(0x9a); }
static void trampoline_0x9b() { panic_handler(0x9b); }
static void trampoline_0x9c() { panic_handler(0x9c); }
static void trampoline_0x9d() { panic_handler(0x9d); }
static void trampoline_0x9e() { panic_handler(0x9e); }
static void trampoline_0x9f() { panic_handler(0x9f); }
static void trampoline_0xa0() { panic_handler(0xa0); }
static void trampoline_0xa1() { panic_handler(0xa1); }
static void trampoline_0xa2() { panic_handler(0xa2); }
static void trampoline_0xa3() { panic_handler(0xa3); }
static void trampoline_0xa4() { panic_handler(0xa4); }
static void trampoline_0xa5() { panic_handler(0xa5); }
static void trampoline_0xa6() { panic_handler(0xa6); }
static void trampoline_0xa7() { panic_handler(0xa7); }
static void trampoline_0xa8() { panic_handler(0xa8); }
static void trampoline_0xa9() { panic_handler(0xa9); }
static void trampoline_0xaa() { panic_handler(0xaa); }
static void trampoline_0xab() { panic_handler(0xab); }
static void trampoline_0xac() { panic_handler(0xac); }
static void trampoline_0xad() { panic_handler(0xad); }
static void trampoline_0xae() { panic_handler(0xae); }
static void trampoline_0xaf() { panic_handler(0xaf); }
static void trampoline_0xb0() { panic_handler(0xb0); }
static void trampoline_0xb1() { panic_handler(0xb1); }
static void trampoline_0xb2() { panic_handler(0xb2); }
static void trampoline_0xb3() { panic_handler(0xb3); }
static void trampoline_0xb4() { panic_handler(0xb4); }
static void trampoline_0xb5() { panic_handler(0xb5); }
static void trampoline_0xb6() { panic_handler(0xb6); }
static void trampoline_0xb7() { panic_handler(0xb7); }
static void trampoline_0xb8() { panic_handler(0xb8); }
static void trampoline_0xb9() { panic_handler(0xb9); }
static void trampoline_0xba() { panic_handler(0xba); }
static void trampoline_0xbb() { panic_handler(0xbb); }
static void trampoline_0xbc() { panic_handler(0xbc); }
static void trampoline_0xbd() { panic_handler(0xbd); }
static void trampoline_0xbe() { panic_handler(0xbe); }
static void trampoline_0xbf() { panic_handler(0xbf); }
static void trampoline_0xc0() { panic_handler(0xc0); }
static void trampoline_0xc1() { panic_handler(0xc1); }
static void trampoline_0xc2() { panic_handler(0xc2); }
static void trampoline_0xc3() { panic_handler(0xc3); }
static void trampoline_0xc4() { panic_handler(0xc4); }
static void trampoline_0xc5() { panic_handler(0xc5); }
static void trampoline_0xc6() { panic_handler(0xc6); }
static void trampoline_0xc7() { panic_handler(0xc7); }
static void trampoline_0xc8() { panic_handler(0xc8); }
static void trampoline_0xc9() { panic_handler(0xc9); }
static void trampoline_0xca() { panic_handler(0xca); }
static void trampoline_0xcb() { panic_handler(0xcb); }
static void trampoline_0xcc() { panic_handler(0xcc); }
static void trampoline_0xcd() { panic_handler(0xcd); }
static void trampoline_0xce() { panic_handler(0xce); }
static void trampoline_0xcf() { panic_handler(0xcf); }
static void trampoline_0xd0() { panic_handler(0xd0); }
static void trampoline_0xd1() { panic_handler(0xd1); }
static void trampoline_0xd2() { panic_handler(0xd2); }
static void trampoline_0xd3() { panic_handler(0xd3); }
static void trampoline_0xd4() { panic_handler(0xd4); }
static void trampoline_0xd5() { panic_handler(0xd5); }
static void trampoline_0xd6() { panic_handler(0xd6); }
static void trampoline_0xd7() { panic_handler(0xd7); }
static void trampoline_0xd8() { panic_handler(0xd8); }
static void trampoline_0xd9() { panic_handler(0xd9); }
static void trampoline_0xda() { panic_handler(0xda); }
static void trampoline_0xdb() { panic_handler(0xdb); }
static void trampoline_0xdc() { panic_handler(0xdc); }
static void trampoline_0xdd() { panic_handler(0xdd); }
static void trampoline_0xde() { panic_handler(0xde); }
static void trampoline_0xdf() { panic_handler(0xdf); }
static void trampoline_0xe0() { panic_handler(0xe0); }
static void trampoline_0xe1() { panic_handler(0xe1); }
static void trampoline_0xe2() { panic_handler(0xe2); }
static void trampoline_0xe3() { panic_handler(0xe3); }
static void trampoline_0xe4() { panic_handler(0xe4); }
static void trampoline_0xe5() { panic_handler(0xe5); }
static void trampoline_0xe6() { panic_handler(0xe6); }
static void trampoline_0xe7() { panic_handler(0xe7); }
static void trampoline_0xe8() { panic_handler(0xe8); }
static void trampoline_0xe9() { panic_handler(0xe9); }
static void trampoline_0xea() { panic_handler(0xea); }
static void trampoline_0xeb() { panic_handler(0xeb); }
static void trampoline_0xec() { panic_handler(0xec); }
static void trampoline_0xed() { panic_handler(0xed); }
static void trampoline_0xee() { panic_handler(0xee); }
static void trampoline_0xef() { panic_handler(0xef); }
static void trampoline_0xf0() { panic_handler(0xf0); }
static void trampoline_0xf1() { panic_handler(0xf1); }
static void trampoline_0xf2() { panic_handler(0xf2); }
static void trampoline_0xf3() { panic_handler(0xf3); }
static void trampoline_0xf4() { panic_handler(0xf4); }
static void trampoline_0xf5() { panic_handler(0xf5); }
static void trampoline_0xf6() { panic_handler(0xf6); }
static void trampoline_0xf7() { panic_handler(0xf7); }
static void trampoline_0xf8() { panic_handler(0xf8); }
static void trampoline_0xf9() { panic_handler(0xf9); }
static void trampoline_0xfa() { panic_handler(0xfa); }
static void trampoline_0xfb() { panic_handler(0xfb); }
static void trampoline_0xfc() { panic_handler(0xfc); }
static void trampoline_0xfd() { panic_handler(0xfd); }
static void trampoline_0xfe() { panic_handler(0xfe); }
static void trampoline_0xff() { panic_handler(0xff); }
static void *trampolines[] = {
	trampoline_0x00, trampoline_0x01, trampoline_0x02, trampoline_0x03,
	trampoline_0x04, trampoline_0x05, trampoline_0x06, trampoline_0x07,
	trampoline_0x08, trampoline_0x09, trampoline_0x0a, trampoline_0x0b,
	trampoline_0x0c, trampoline_0x0d, trampoline_0x0e, trampoline_0x0f,
	trampoline_0x10, trampoline_0x11, trampoline_0x12, trampoline_0x13,
	trampoline_0x14, trampoline_0x15, trampoline_0x16, trampoline_0x17,
	trampoline_0x18, trampoline_0x19, trampoline_0x1a, trampoline_0x1b,
	trampoline_0x1c, trampoline_0x1d, trampoline_0x1e, trampoline_0x1f,
	trampoline_0x20, trampoline_0x21, trampoline_0x22, trampoline_0x23,
	trampoline_0x24, trampoline_0x25, trampoline_0x26, trampoline_0x27,
	trampoline_0x28, trampoline_0x29, trampoline_0x2a, trampoline_0x2b,
	trampoline_0x2c, trampoline_0x2d, trampoline_0x2e, trampoline_0x2f,
	trampoline_0x30, trampoline_0x31, trampoline_0x32, trampoline_0x33,
	trampoline_0x34, trampoline_0x35, trampoline_0x36, trampoline_0x37,
	trampoline_0x38, trampoline_0x39, trampoline_0x3a, trampoline_0x3b,
	trampoline_0x3c, trampoline_0x3d, trampoline_0x3e, trampoline_0x3f,
	trampoline_0x40, trampoline_0x41, trampoline_0x42, trampoline_0x43,
	trampoline_0x44, trampoline_0x45, trampoline_0x46, trampoline_0x47,
	trampoline_0x48, trampoline_0x49, trampoline_0x4a, trampoline_0x4b,
	trampoline_0x4c, trampoline_0x4d, trampoline_0x4e, trampoline_0x4f,
	trampoline_0x50, trampoline_0x51, trampoline_0x52, trampoline_0x53,
	trampoline_0x54, trampoline_0x55, trampoline_0x56, trampoline_0x57,
	trampoline_0x58, trampoline_0x59, trampoline_0x5a, trampoline_0x5b,
	trampoline_0x5c, trampoline_0x5d, trampoline_0x5e, trampoline_0x5f,
	trampoline_0x60, trampoline_0x61, trampoline_0x62, trampoline_0x63,
	trampoline_0x64, trampoline_0x65, trampoline_0x66, trampoline_0x67,
	trampoline_0x68, trampoline_0x69, trampoline_0x6a, trampoline_0x6b,
	trampoline_0x6c, trampoline_0x6d, trampoline_0x6e, trampoline_0x6f,
	trampoline_0x70, trampoline_0x71, trampoline_0x72, trampoline_0x73,
	trampoline_0x74, trampoline_0x75, trampoline_0x76, trampoline_0x77,
	trampoline_0x78, trampoline_0x79, trampoline_0x7a, trampoline_0x7b,
	trampoline_0x7c, trampoline_0x7d, trampoline_0x7e, trampoline_0x7f,
	trampoline_0x80, trampoline_0x81, trampoline_0x82, trampoline_0x83,
	trampoline_0x84, trampoline_0x85, trampoline_0x86, trampoline_0x87,
	trampoline_0x88, trampoline_0x89, trampoline_0x8a, trampoline_0x8b,
	trampoline_0x8c, trampoline_0x8d, trampoline_0x8e, trampoline_0x8f,
	trampoline_0x90, trampoline_0x91, trampoline_0x92, trampoline_0x93,
	trampoline_0x94, trampoline_0x95, trampoline_0x96, trampoline_0x97,
	trampoline_0x98, trampoline_0x99, trampoline_0x9a, trampoline_0x9b,
	trampoline_0x9c, trampoline_0x9d, trampoline_0x9e, trampoline_0x9f,
	trampoline_0xa0, trampoline_0xa1, trampoline_0xa2, trampoline_0xa3,
	trampoline_0xa4, trampoline_0xa5, trampoline_0xa6, trampoline_0xa7,
	trampoline_0xa8, trampoline_0xa9, trampoline_0xaa, trampoline_0xab,
	trampoline_0xac, trampoline_0xad, trampoline_0xae, trampoline_0xaf,
	trampoline_0xb0, trampoline_0xb1, trampoline_0xb2, trampoline_0xb3,
	trampoline_0xb4, trampoline_0xb5, trampoline_0xb6, trampoline_0xb7,
	trampoline_0xb8, trampoline_0xb9, trampoline_0xba, trampoline_0xbb,
	trampoline_0xbc, trampoline_0xbd, trampoline_0xbe, trampoline_0xbf,
	trampoline_0xc0, trampoline_0xc1, trampoline_0xc2, trampoline_0xc3,
	trampoline_0xc4, trampoline_0xc5, trampoline_0xc6, trampoline_0xc7,
	trampoline_0xc8, trampoline_0xc9, trampoline_0xca, trampoline_0xcb,
	trampoline_0xcc, trampoline_0xcd, trampoline_0xce, trampoline_0xcf,
	trampoline_0xd0, trampoline_0xd1, trampoline_0xd2, trampoline_0xd3,
	trampoline_0xd4, trampoline_0xd5, trampoline_0xd6, trampoline_0xd7,
	trampoline_0xd8, trampoline_0xd9, trampoline_0xda, trampoline_0xdb,
	trampoline_0xdc, trampoline_0xdd, trampoline_0xde, trampoline_0xdf,
	trampoline_0xe0, trampoline_0xe1, trampoline_0xe2, trampoline_0xe3,
	trampoline_0xe4, trampoline_0xe5, trampoline_0xe6, trampoline_0xe7,
	trampoline_0xe8, trampoline_0xe9, trampoline_0xea, trampoline_0xeb,
	trampoline_0xec, trampoline_0xed, trampoline_0xee, trampoline_0xef,
	trampoline_0xf0, trampoline_0xf1, trampoline_0xf2, trampoline_0xf3,
	trampoline_0xf4, trampoline_0xf5, trampoline_0xf6, trampoline_0xf7,
	trampoline_0xf8, trampoline_0xf9, trampoline_0xfa, trampoline_0xfb,
	trampoline_0xfc, trampoline_0xfd, trampoline_0xfe, trampoline_0xff
};
extern void idt_load(void *);
void idt_setup() {
    u32 idt_sz = sizeof(trampolines) / sizeof(trampolines[0]);
    gate_descriptor_t *idt = (gate_descriptor_t *) kernel_malloc(idt_sz * sizeof(gate_descriptor_t));
    if (!idt) {
        print("Not enough memory to allocate idt\n");
        return;
    }
    for (int i = 0; i <= idt_sz; i++) {
        gate_descriptor_t gd;
        byte_t *handler = trampolines[i];
        gd.offset_low = (u16) handler;
        gd.segselector = 0x8;
        gd.nargs = 0x0;
        gd.unused0 = 0x0;
        gd.gate_type = INTERRUPT_GATE;
        gd.unused1 = 0x0;
        gd.dpl = 0x0;
        gd.existance_bit = 1;
        gd.offset_high = (u16) (((u32) handler) >> 16);
        idt[i] = gd;
    }
    idt_descriptor_t idtd = {
        .idt_sz = idt_sz * sizeof(gate_descriptor_t) - 1, 
        .idt_addr = (u32) idt
    };
    idt_load(&idtd);
}
