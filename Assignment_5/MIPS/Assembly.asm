.data 0x10000000
.text
.globl main
main: 
Label1:
li $t0, 0
sw $t0, 0x10000000($0)
li $t0, 0
sw $t0, 0x10000004($0)
li $t0, 4
sw $t0, 0x10000004($0)
li $t0, 3
lw $t1, 0x10000004($0)
mult $t0, $t1
mflo $v0
sw $v0, 0x10000004($0)
li $t0, 0
sw $t0, 0x10002ee8($0)
li $t0, 1
sw $t0, 0x10002ee8($0)
li $t0, 0
sw $t0, 0x10002eec($0)
li $t0, 2
sw $t0, 0x10002eec($0)
lw $t0, 0x10002ee8($0)
li $t1, 4
mult $t0, $t1
mflo $v0
sw $v0, 0x10002ee8($0)
lw $t0, 0x10002ee8($0)
lw $t1, 0x10002eec($0)
add $v0, $t0, $t1
sw $v0, 0x10002eec($0)
li $t0, 0
sw $t0, 0x10002ef0($0)
li $t0, 4
sw $t0, 0x10002ef0($0)
li $t3, 268435456
lw $t4, 0x10002eec($0)
sll $t4, $t4, 2
add $t5, $t3, $t4
lw $t0, 0x10002ef0($0)
sw $t0, 0($t5)
jr $ra
