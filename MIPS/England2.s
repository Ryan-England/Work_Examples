# CS24 assignment 3
# Fall 2022, Ryan England

.globl main

.text
main: addi $v0, $zero, 4 # print welcome
  la $a0, welcome
  syscall

  li $v0, 4 # print prompt
  la $a0, prompt
  syscall

  li $v0, 5 # get how many primes to print
  syscall
  move $s0, $v0 # and store them in $s0, not $t0

  li $s1, 1 # Load $s1 with the first prime - 1

prime:
  blt $s0, 1, exit # if the number of primes is < 1, exit
  addi $s1, $s1, 1 # set up to check the next number

  move $a0, $s1 # Load $s1 as an argument
  jal test_prime
  move $s2, $v0 # Load results into $s2

  beq $s2, $zero, prime #if not prime, try next number.
  li $v0, 1 # print prime number
  move $a0, $s1
  syscall

  li $v0, 4 # print a newline
  la $a0, newline
  syscall

  addi $s0, $s0, -1 # One down, $s0 more to go!
  j prime

exit:

  li $v0, 10 # exit program
  syscall

# Checks to see if the argument ($a0) is a prime number
test_prime: # $t0 is argument, $t1 is half of argument to check for factors
  move $t0, $a0

  li $t1, 2
  div $t0, $t1 # divide by two to save time
  mflo $t1 # and store in $t1

  add $t3, $zero, 2 # change $t3 to the end check

loop:
  blt $t1, $t3, end_loop

  div $t0, $t1
  mfhi $t2

  beq $t2, $zero, not_prime # If $t0 % $t1 = 0

  addi $t1, $t1, -1 # subtract to check the next lowest number
  j loop

not_prime:
  li $v0, 0 # not a prime
  jr $ra

end_loop:
  li $v0, 1 #is a prime
  jr $ra

.data
welcome:  .asciiz "This program will print out prime numbers!\n"
prompt:   .asciiz "How many primes do you want? (must be >=1): "
newline:  .asciiz "\n"
