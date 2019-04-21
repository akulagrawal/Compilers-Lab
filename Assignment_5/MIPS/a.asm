.data 0x10000000

msg1: 
	.globl main
	.text

main: 
li $t0, 2
sw $t0, 0x10000000($0)

li $t0, 3
sw $t0, 0x10000010($0)

li $t0, 0
sw $t0, 0x10001000($0)

lw $t0, 0x10000000($0)
lw $t1, 0x10000100($0)
add $v0, $t0, $t1

sw $v0, 0x10001000($0)
li $v0, 1
lw $a0, 0x10001000($0)
syscall

jr $ra