.data 0x10000000
msg1: .globl main
main: 
li $t0, 2
sw $t0, 0x10000001($0)
li $t0, 3
sw $t0, 0x10000002($0)
li $t0, 0
sw $t0, 0x10000003($0)
lw $t0, 0x10000001($0)
lw $t1, 0x10000002($0)
add $v0, $t0, $t1
sw $v0, 0x10000003($0)
