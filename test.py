s = 0
with open("./build/boot.img", "rb") as f:
    for i in range(512):
        byte = f.read(1)
        s += int.from_bytes(byte)
    # for i in range(512):
    #     byte = f.read(1)
    #     s += int.from_bytes(byte)

print(s)
