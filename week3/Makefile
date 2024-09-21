all: ex_head_nlines ex_tail_nlines ex_stat

ex_head_nlines: ex_head_nlines.o
	gcc -O -o ex_head_nlines ex_head_nlines.o
ex_tail_nlines: ex_tail_nlines.o
	gcc -O -o ex_tail_nlines ex_tail_nlines.o
ex_stat: ex_stat.o
	gcc -O -o ex_stat ex_stat.o

ex_head_nlines.o: ex_head_nlines.c
	gcc -O -c -o ex_head_nlines.o ex_head_nlines.c
ex_tail_nlines.o: ex_tail_nlines.c
	gcc -O -c -o ex_tail_nlines.o ex_tail_nlines.c
ex_stat.o: ex_stat.c
	gcc -O -c -o ex_stat.o ex_stat.c

clean:
	rm -f *.o ex_head_nlines ex_tail_nlines ex_stat

