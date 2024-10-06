# import os
import random
file = open("gen", "w")
# for i in range(0, 1024):
sm = 448 * 1024 - 512
string = str(random.randbytes(sm))
out = ""
sum = 0
for i in string:
    if sum >= (sm):
        break
    sum += 1
    out += i
print(sum)
file.write(out)
