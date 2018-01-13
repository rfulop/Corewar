.name "zork"
.comment "just a basic living prog"

		live %-1
		ld %0, r5
		st r5, -12
		zjmp %-200
#		ld %8888, r6
#		fork %10
#		ld %0, r14
#		zjmp %-80
#		live %0
#		st r6, 200
#		ld %50, r5
#		ld %1, r5
#		ld %0, r6
#		zjmp %-50
#		ld %1, r5
#		ld %1, r5
#		ld %1, r5
#		fork %0
#		live %-1
#		fork %2
#		ld %-1, r2
#		ld %-1, r2
#		live %-1
#		sti	r2,%400,%0
#		sti	r3,%410,%0
#		live %-3
