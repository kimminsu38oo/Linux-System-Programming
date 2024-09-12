all: ex_cat ex_cp ex_head ex_tail

ex_cat: ex_cat.o
	gcc -o ex_cat ex_cat.o
ex_cp: ex_cp.o
	gcc -o ex_cp ex_cp.o
ex_head: ex_head.o
	gcc -o ex_head ex_head.o
ex_tail: ex_tail.o
	gcc -o ex_tail ex_tail.o

ex_cat.o: ex_cat.c
	gcc -c -o ex_cat.o ex_cat.c
ex_cp.o: ex_cp.c
	gcc -c -o ex_cp.o ex_cp.c
ex_head.o: ex_head.c
	gcc -c -o ex_head.o ex_head.c
ex_tail.o: ex_tail.c
	gcc -c -o ex_tail.o ex_tail.c

clean:
	rm *.o ex_cat ex_cp ex_head ex_tail




