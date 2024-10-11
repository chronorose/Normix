gen = open("gen", "rb")
from_vm = open("to_check", "rb")
asm = open("build/boot.bin", "rb")
gen_str = gen.read()
from_vm_str = from_vm.read()
asm_str = asm.read()
s1 = 0
s2 = 0
for i in range(len(gen_str)):
    s1 += gen_str[i]
for i in range(len(from_vm_str)):
    s2 += from_vm_str[i]
for i in range(len(asm_str)):
    s1 += asm_str[i]
print(s1)
print(s2)
