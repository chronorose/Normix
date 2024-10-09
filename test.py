import random


def gen(fpath):
    with open(fpath, "wb") as f:
        size = 0x60000 - 0x200
        content = [random.randbytes(1) for _ in range(size)]
        for byte in content:
            f.write(byte)


def getbytesum(fpath):
    s = 0
    with open(fpath, "rb") as f:
        content = f.read()
        for i in range(len(content)):
            s += content[i]
    return s


print(getbytesum("./gen") + getbytesum("./build/boot.bin"))
print(getbytesum("./mem.dump"))
