.name "zork"
.comment "just a basic living prog"

		st		r10, 400
		fork	%23
		ld		%0, r2
		zjmp	%-25
		live	%0
		live	%0
		ld		%1879768882, r12
		live	%0
		live	%0
		live	%0
		st		r12, -49
#		ld %50, r5
#		st r5, -521
#		sti r5, %-521, %0
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
