
                         Simple Stack Machine in C
                         =========================


Instruction Set
---------------

Intentionally minimal,  consisting of mostly stack and control flow operations.
Missing functionality may be provided by the below libraries.

hlt     	- 	       	halt
psh     	-		push (immediate)
pop     	-		pop element from stack
dpl     	-    	     	duplicate top stack element
swp     	-	       	swap top two stack elements
cyc		-               cycle stack (bottom element moved to top)
add     	-		add top two stack elements
cmp		-		compare top two stack elements
out     	-          	print top stack element
inp		-	   	push user input to stack
cbr     	-               branch to address arg1 if not arg2 (from stack)
ubr		-		unconditional branch
crt		-	   	conditional return
urt		-	   	unconditional return
wrt		-		write to memory (s1 -> m[s0])
lde		-		load from memory (m[s0])


BIOS
----

A few useful IO procedures.

printString	-		print from stack until reaching terminator char
printNum	-	  	print the top  element on the stack as a number


Standard Library
----------------

A small standard library complements the BIOS to provide a few subroutines re-
sponsible for arithmetic and logic operations.

subtract        -               subtract top two stack elements
multiply        -	      	multiply top two stack elements
divide          -	      	divide top two stack elements (s0/s1)
