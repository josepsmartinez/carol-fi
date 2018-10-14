all: generate_input read_input

test_generation: all
	clear
	./generate_input.out
	./read_input.out

malloc2d: malloc2d.c malloc2d.h
	gcc malloc2d.c -c

input_synth: input_synth.c input_synth.h
	gcc input_synth.c -c

generate_input: generate_input.c malloc2d input_synth
	gcc malloc2d.o input_synth.o generate_input.c -o generate_input.out

read_input: read_input.c malloc2d input_synth
	gcc malloc2d.o input_synth.o read_input.c -o read_input.out


