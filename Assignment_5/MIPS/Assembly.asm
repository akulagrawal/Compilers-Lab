.data 0x10000000
.text
.globl main
main: 
li $t0, 2
sw $t0, 0x10000000($0)
li $t0, 3
sw $t0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10000008($0)
lw $t0, 0x10000008($0)
beqz $t0, Label1
li $t0, 1
sw $t0, 0x1000000d($0)
Label1:
li $t0, 5
sw $t0, 0x10000010($0)
jr $ra
