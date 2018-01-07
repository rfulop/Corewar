.name "zork"
.comment "just a basic living prog"

		live %50
		ld %0, r3
		ld %2, r5
		st r3, 256
		zjmp %-200
		ld %1, r6
		zjmp %-200
