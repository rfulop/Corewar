.name "zork"
.comment "just a basic living prog"

	sti r1, %0,%0
	st r2, :do
	st r2, :re
	ld %728065, r4
	sti r4, %:re, %4
	live %0
	live %0
do:	live %0
re:	live %0
