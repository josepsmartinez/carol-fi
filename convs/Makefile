DATA_OBJS = ../data/malloc2d.o ../data/input_synth.o


#
all: linear dft dft2

clean:
	rm *.o *.out -f

# builds from data/
data_deps:
	cd ../data ; make all

# implementations builds
linear: linear.c data_deps
	gcc -I ../data/ $(DATA_OBJS) linear.c -lm -o linear.out

dft: dft.c
	gcc dft.c -lm -o dft.out

dft2: dft2.c
	gcc -I ../data/ $(DATA_OBJS) dft2.c -lm -o dft2.out

# implementations execution
run_all: clean run_linear run_dft2

run_linear: linear
	cd .. ; ./convs/linear.out ; cat output.txt | wc -l

run_dft2: dft2
	./dft2.out
