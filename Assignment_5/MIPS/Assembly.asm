.data 0x10000000
.text
.globl main
main: 
Label3:
li $t0, 0
sw $t0, 0x10000000($0)
li $t0, 0
sw $t0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10000008($0)
li $t0, 0
sw $t0, 0x1000000c($0)
li $t0, 0
sw $t0, 0x1000000c($0)
lw $t0, 0x1000000c($0)
sw $t0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10000010($0)
lw $t0, 0x10000004($0)
sw $t0, 0x10000010($0)
li $t0, 0
sw $t0, 0x10000014($0)
li $t0, 4
sw $t0, 0x10000014($0)
Label2:
li $t2, 1
lw $t0, 0x10000010($0)
lw $t1, 0x10000014($0)
blt $t0, $t1, Label4
li $t2, 0
Label4:
sw $t2, 0x10000010($0)
lw $t0, 0x10000010($0)
beqz $t0, Label1
li $t0, 0
sw $t0, 0x10000018($0)
lw $t0, 0x10000004($0)
sw $t0, 0x10000018($0)
li $t0, 0
sw $t0, 0x1000001c($0)
li $t0, 1
sw $t0, 0x1000001c($0)
lw $t0, 0x10000018($0)
lw $t1, 0x1000001c($0)
add $v0, $t0, $t1
sw $v0, 0x10000018($0)
lw $t0, 0x10000018($0)
sw $t0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10000020($0)
lw $t0, 0x10000008($0)
sw $t0, 0x10000020($0)
li $t0, 0
sw $t0, 0x10000024($0)
li $t0, 1
sw $t0, 0x10000024($0)
lw $t0, 0x10000020($0)
lw $t1, 0x10000024($0)
add $v0, $t0, $t1
sw $v0, 0x10000020($0)
lw $t0, 0x10000020($0)
sw $t0, 0x10000008($0)
lw $t0, 0x10000004($0)
sw $t0, 0x10000010($0)
move $a0, $t0
li $v0, 1
syscall
j Label2
Label1:
jr $ra