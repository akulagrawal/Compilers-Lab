.data 0x10000000
.text
.globl main
main: 
Label1:
li.s $f0, 0.0
s.s $f0, 0x10000000($0)
li $t0, 0
sw $t0, 0x10000004($0)
li $t0, 1
sw $t0, 0x10000004($0)
lw $t0, 0x10000004($0)
sw $t0, 0x10000008($0)
jr $ra
Label2:
li $t0, 0
sw $t0, 0x1000000c($0)
li $t0, 0
sw $t0, 0x10000010($0)
li $t0, 0
sw $t0, 0x10000014($0)
li $t0, 1
sw $t0, 0x10000014($0)
lw $t0, 0x10000014($0)
sub $sp, $sp, 4
sw $t0, ($sp)
jal Label1
li.s $f0, 0.0
s.s $f0, 0x10000018($0)
l.s $f0, 0x10000000($0)
s.s $f0, 0x10000018($0)
jr $ra
