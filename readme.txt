
                         Simple Stack Machine in C
                         =========================


Instruction Set
---------------

The instruction set is intentionally minimal,  consisting majoritively of stack
and control  flow operations.  None of these instructions pop their  arguments.

hlt     	- 	       	halt
psh     	-		push (immediate)
pop     	-		pop element from stack
dpl     	-    	     	duplicate top stack element
swp     	-	       	swap top two stack elements
cyc		-               cycle stack (bottom element moved to top)
add     	-		add top two stack elements
cmp		-	   	compare top stack elements
out     	-          	print top stack element
inp		-	   	push user input to stack
cbr     	-               branch to address arg1 if not arg2 (from stack)
ubr		-		unconditional branch
crt		-	   	conditional return
urt		-	   	unconditional return


BIOS
----

While  a minimal  instruction  set has  its advantages  it can make certain  IO
operations tedious. The BIOS exists to make common tasks simpler by providing a
small set of useful procedures.

printString	-		print from stack until reaching terminator char
printNum	-	  	print the top element on the stack as a number


Standard Library
----------------

The BIOS is complemented with a small standard library to provide a few subrou-
tines responsible for arithmetic and logic operations.

subtract        -               subtract top two stack elements
multiply        -	      	multiply top two stack elements
divide          -	      	divide top two stack elements (s0/s1)
