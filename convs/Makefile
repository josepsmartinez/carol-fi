CC = gcc -g
DATA_OBJS = ../data/malloc2d.o ../data/input_synth.o


#
all: linear dft dft2

clean:
	rm *.o -f

# builds from data/ (does not generate input again)
data_deps:
	cd ../data ; make all

# implementations builds
linear: linear.c data_deps
	$(CC) -I ../data/ $(DATA_OBJS) linear.c -lm -o linear

fft: fft.cpp data_deps
	g++ -I ../data/ $(DATA_OBJS) fft.cpp -lm -o fft

dft: dft.c data_deps
	$(CC) dft.c -lm -o dft

dft2: dft2.c data_deps
	$(CC) -O3 -I ../data/ $(DATA_OBJS) dft2.c -lm -o dft2

# implementations execution
run_all: clean run_linear run_dft2

run_linear: linear
	./linear ../data/new_matrix.bin ../data/new_kernels.bin output.txt
	cat output.txt | wc -l

run_fft: fft
	./fft ../data/new_matrix.bin ../data/new_kernels.bin output.txt

run_dft: dft
	./dft

run_dft2: dft2
	./dft2 ../data/new_matrix.bin ../data/new_kernels.bin output.txt
