def intergen(num):
    return f"static void tramplin_{hex(num)[2:]}()" + \
            " {" + f" panic_handler({hex(num)}); " + "}"


def arrgen(start, end):
    string = "static void** tramplins = { "
    for i in range(start, end):
        string = string + f"tramplin_{hex(i)[2:]}, "
    string = string + " };"
    return string


for i in range(0, 256):
    print(intergen(i))
print(arrgen(0, 256))
