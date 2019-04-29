.data 0x10000000
.text
.globl main
main: 
Label3:
li $t0, 0
sw $t0, 0x10000000($0)
li $t0, 0
sw $t0, 0x10000004($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000008($0)
li $t0, 0
sw $t0, 0x1000000c($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10000010($0)
li $t0, 0
sw $t0, 0x10000014($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000018($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000014($0)
li $t0, 0
sw $t0, 0x1000001c($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000010($0)
li $t0, 0
sw $t0, 0x10000020($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000024($0)
Label2:
li $v0, 1
sw $v0, 0x1000001c($0)
lw $t0, 0x1000001c($0)
lw $t1, 0x10000020($0)
blt $t0, $t1, Label4
li $v0, 0
sw $v0, 0x1000001c($0)
Label4:
lw $t0, 0x1000001c($0)
beqz $t0, Label1
li $t0, 0
sw $t0, 0x10000028($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000010($0)
li $t0, 0
sw $t0, 0x1000002c($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000030($0)
lw $t0, 0x10000028($0)
lw $t1, 0x1000002c($0)
add $v0, $t0, $t1
sw $v0, 0x10000028($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000028($0)
li $t0, 0
sw $t0, 0x10000034($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x1000000c($0)
li $t0, 0
sw $t0, 0x10000038($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000030($0)
lw $t0, 0x10000034($0)
lw $t1, 0x10000038($0)
add $v0, $t0, $t1
sw $v0, 0x10000034($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000034($0)
j Label2
li $t0, 0
sw $t0, 0x1000003c($0)
lw $t0, 0xfffffff($0)
sw $t0, 0x10000030($0)
Label1:
lw $t0, 0xfffffff($0)
sw $t0, 0x1000003c($0)
jr $ra
