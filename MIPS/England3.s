# CS24 Assignment 7
# Fall 2022, Ryan England

.globl main

.text
main:

  add $v0, $zero, 4 #print out intro
  la $a0, welcome
  syscall

  li $v0, 4 #print out the prompt
  la $a0, first
  syscall

  li $v0, 5 #store the first int (M)
  syscall
  move $s0, $v0

  blt $s0, $zero, exit # Make sure it's >= 0.

  li $v0, 4 #print out second prompt
  la $a0, second
  syscall

  li $v0, 5 #store the second int (N)
  syscall
  move $s1, $v0

  blt $s1, $zero, exit # Make sure it's also >= 0.

  blt $s1, $s0, notSwap # If N < M, we're good. Otherwise, we swap them.

  move $s2, $s0
  move $s0, $s1
  move $s1, $s2

notSwap:
  #insert function call here
  move $a0, $s0
  move $a1, $s1
  jal Euclid
  move $s2, $v0

  li $v0, 4 #print out the ending prompt
  la $a0, gcd
  syscall

  li $v0, 1 #print out M
  move $a0, $s0
  syscall

  li $v0, 4 #print out the joiner...
  la $a0, join
  syscall

  li $v0, 1 #print out N
  move $a0, $s1
  syscall

  li $v0, 4 #and then finally...
  la $a0, finish
  syscall

  li $v0, 1 #print the result
  move $a0, $s2
  syscall

  li $v0, 4 #and it's all on one nice and tidy line of output.
  la $a0, newline
  syscall

exit:
  li $v0, 10 #exit
  syscall

# This function recursively searches for the GCD, using Euclid's Algorithm.
# Inputs M, N (M > N)
# Returns the GCD (as an int)
Euclid: move $t0, $a0
  move $t1, $a1

  beq $t1, $zero, end

  div $t0, $t1
  mfhi $t0 # We don't need M anymore, so we'll use it for the remainder

  addi $sp, $sp, -4 # allocate some space to memory...
  sw $ra, 0($sp) # and let's store the return address for the recursion.

  move $a0, $t1 # now N becomes M
  move $a1, $t0 # and M % N becomes N.
  jal Euclid # Recursion!
  # And then the return value is in $v0, so we don't need to move it.

  lw $ra, 0($sp) # let's restore the return address...
  addi $sp, $sp, 4 # and release the memory we used.

  # Just as a reminder, the return value is already in $v0.
  jr $ra

end:
  move $v0, $t0

  jr $ra

.data
welcome: .asciiz "Euclid's GCD Algorithm\n"
first: .asciiz "Please enter the 1st integer (int >= 0): "
second: .asciiz "Please enter the 2nd integer (int >= 0): "
newline: .asciiz "\n"
gcd: .asciiz "The GCD of "
join: .asciiz " and "
finish: .asciiz " is: "
