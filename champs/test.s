.name "test"
.comment "i m testing"

aff r3 #0x10 + 2 octs
lfork %200 # 0x0d  + 2 octs
sti r2, %23, %34 # 0x0b + ocp + 1 oct + 2 octs + 2 octs
sti r1, r2, r3 # 0x0b + ocp + 1 + 1 + 1
