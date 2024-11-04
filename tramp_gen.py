def gen_trampolines():
    with open("./src/trampolines.c", "a") as f:
        s = ""
        for i in range(0x0, 0xFF + 1):
            s += f"static void trampoline_{i:#0{4}x}() {{ panic_handler({i:#0{4}x}); }}"
            s += "\n"
        f.write(s)


def gen_lookup():
    with open("./src/trampolines.c", "a") as f:
        s = "static void *trampolines[] = {\n\t"
        for i in range(0x0, 0xFF + 1):
            s += f"trampoline_{i:#0{4}x}"
            if i != 0xFF:
                s += ","
            s += " " if (i + 1) % 4 != 0 else "\n\t"
        s += "};"
        f.write(s)


gen_trampolines()
gen_lookup()
