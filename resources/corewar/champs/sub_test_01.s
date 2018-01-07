.name "zork"
.comment "just a basic living prog"

#test si on ne check pas les types d arg dans l ocp un direct peut se retrouver
#a etre utiliser comme un registre et SEGFAULT !

		ld %2500, r12
		ld %100, r13
		ld %2487353601, r2
		ld %90439936, r3
		ld %3489153537, r4

#		ld %1476460866, r4
#		sti r2, %:panda, %1
		sti r3, %:panda2, %0
		sti r4, %:panda2, %4
		sti r4, %:panda3, %1
panda:	sub r12, r13, r14
		live %0
		live %0
panda2:	sub r12, r13, r14
		live %0
		live %0
#panda3:	sub r12, r13, r14
