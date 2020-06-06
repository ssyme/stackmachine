Simple Stack Machine in C
=========================

Instruction Set
---------------

hlt	-		halt
psh	-		push (immediate)
dpl	-		duplicate top stack element
swp	-		swap top two stack elements
pop	-		pop element from stack (send to purgatory)
pll	-		pull popped (from purgatory)
add	-		sum top two stack elements
out	-		print top stack element (doesn't pop)
jpz	-		jump to address arg1 if not arg2 (from stack)
