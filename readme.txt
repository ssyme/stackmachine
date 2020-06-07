Simple Stack Machine in C
=========================

Instruction Set
---------------

The instruction set is intentionally minimal and consists majoritively of stack operations.

hlt     -          halt
psh     -          push (immediate)
dpl     -          duplicate top stack element
swp     -          swap top two stack elements
pop     -          pop element from stack (send to purgatory)
pll     -          pull from purgatory (popped)
add     -          add top two stack elements
out     -          print top stack element (doesn't pop)
jpz     -          jump to address arg1 if not arg2 (from stack)


Standard Library
----------------

The instruction set is extended with a minimal standard library which provides useful helper functions to carry out tedious arithmetic and IO operations.

subtract       -          subtract top two stack elements
multiply       -          multiply top two stack elements
divide         -          divide top two stack elements (s0/s1)
print          -          out from stack until reaching 0
printDigit     -          print top element on stack as a number

