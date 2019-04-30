.data 0x10000000
.text
.globl main
main: 
Label4:
li $t0, 0
sw $t0, 0x10000000($0)
li $t0, 0
sw $t0, 0x10000004($0)
li $t0, 5
sw $t0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10000008($0)
lw $t0, 0x10000004($0)
sw $t0, 0x10000008($0)
li $t0, 0
sw $t0, 0x1000000c($0)
li $t0, 10
sw $t0, 0x1000000c($0)
li $t0, 0
sw $t0, 0x10000010($0)
lw $t0, 0x1000000c($0)
sw $t0, 0x10000010($0)
li $t0, 0
sw $t0, 0x10000014($0)
lw $t0, 0x10000010($0)
sw $t0, 0x10000014($0)
li $t0, 0
sw $t0, 0x10000018($0)
li $t0, 3
sw $t0, 0x10000018($0)
li $t2, 1
lw $t0, 0x10000014($0)
lw $t1, 0x10000018($0)
blt $t0, $t1, Label5
li $t2, 0
Label5:
sw $t2, 0x10000014($0)
lw $t0, 0x10000014($0)
bnez $t0, Label1
li $t0, 0
sw $t0, 0x1000001c($0)
lw $t0, 0x10000008($0)
sw $t0, 0x1000001c($0)
li $t0, 0
sw $t0, 0x10000020($0)
li $t0, 2
sw $t0, 0x10000020($0)
li $t2, 1
lw $t0, 0x1000001c($0)
lw $t1, 0x10000020($0)
bgt $t0, $t1, Label6
li $t2, 0
Label6:
sw $t2, 0x1000001c($0)
Label1:
l.s $f0, 0xfffffff($0)
li.s $f1, 0.0
c.eq.s $f0, $f1
bc1t Label2
li $t0, 0
sw $t0, 0x10000024($0)
li $t0, 3
sw $t0, 0x10000024($0)
lw $t0, 0x10000024($0)
sw $t0, 0x10000008($0)
j Label3
Label2:
li $t0, 0
sw $t0, 0x10000028($0)
li $t0, 15
sw $t0, 0x10000028($0)
lw $t0, 0x10000028($0)
sw $t0, 0x10000008($0)
Label3:
li $t0, 0
sw $t0, 0x1000002c($0)
li $t0, 1
sw $t0, 0x1000002c($0)
lw $t0, 0x1000002c($0)
sw $t0, 0x10000000($0)
jr $ra
