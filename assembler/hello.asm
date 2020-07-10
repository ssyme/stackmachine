:USING SMASM:

..start:
	psh '\0'
	psh '\n'
	psh '!'
	psh 'D'
	psh 'L'
	psh 'R'
	psh 'O'
	psh 'W'
	psh ' '
	psh 'O'
	psh 'L'
	psh 'L'
	psh 'E'
	psh 'H'

..loop:
	dpl
	psh '\0'
	cmp		;; check for string terminator
	psh ..end
	cbr
	pop
	out
	pop
	psh ..loop
	ubr

..end:
	hlt
