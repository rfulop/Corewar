.name "zork"
.comment "just a basic living prog"

		ld %32896502, r3
		sti r3, %-60, %0
		ld %42833333, r3
		sti r3, %-68, %0
		ld %42234124, r3
		sti r3, %-76, %0
		ld %24535656, r3
		sti r3, %-84, %0
		ld %32435567, r3
		sti r3, %-92, %0
		ld %33458663, r3
		sti r3, %-100, %0
		ld %37322115, r3
		sti r3, %-108, %0
		ld %65639423, r3
		sti r3, %-116, %0
		ld %85634452, r3
		sti r3, %-124, %0

		ld -655, r4
		sti r4, %400, %0

#		sti r3, %-58, %0
#		sti r3, %-57, %0
#		sti r3, %-56, %0
#		zjmp %-71
#		st r2, -3
#		ld %0, r2
#		sti	r2,%5000,%0
#		sti	r2,%-200,%0
#		sti	r2,%-600,%0
#		sti	r2,%-768,%0
#		sti	r2,%3200,%0
#		st r2, -522
#		st r2, 600
#		st r2, -200
#		st r2, 522
#		st r2, -622
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
