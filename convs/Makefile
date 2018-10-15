all: linear dft dft2
clean:
	rm *.o *.out -f

#
linear: linear.c ../data/malloc2d.o
	gcc -I ../data/ ../data/malloc2d.o linear.c -lm -o linear.out

dft: dft.c
	gcc dft.c -lm -o dft.out

dft2: dft2.c ../data/malloc2d.o
	gcc -I ../data/ ../data/malloc2d.o dft2.c -lm -o dft2.out

#
run_linear: linear
	./linear.out

run_df2: dft2
	./dft2.out
