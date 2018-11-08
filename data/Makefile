CC = gcc -g

all: clean generate_input read_input

clean:
	rm *.o *.out -f

clean_data:
	rm *.bin *.txt -f


malloc2d: malloc2d.c malloc2d.h
	$(CC) malloc2d.c -c

input_synth: input_synth.c input_synth.h
	$(CC) input_synth.c -c

generate_input: generate_input.c malloc2d input_synth
	$(CC) malloc2d.o input_synth.o generate_input.c -o generate_input.out

read_input: read_input.c malloc2d input_synth
	$(CC) malloc2d.o input_synth.o read_input.c -o read_input.out

#
reset_data: all
	./generate_input.out
	cd .. ; ./data/read_input.out
