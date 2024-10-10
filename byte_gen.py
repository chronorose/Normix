import random
file = open("gen", "wb")
# for i in range(0, 1024):
sm = 0x80000 - 0xf800 - 0x200
string = [random.randbytes(1) for _ in range(sm)]
# sum = 0
for i in string:
    file.write(i)
    # if sum >= (sm):
    #     break
    # sum += 1
    # out += i
# print(sum)
# file.write(bytes(out, encoding='utf8'))
