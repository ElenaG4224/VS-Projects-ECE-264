WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

SRCS = main.c binary_tree.c
OBJS = $(SRCS:%.c=%.o)

hw11: $(OBJS) 
	$(GCC) $(OBJS) -o hw11

.c.o: 
	$(GCC) -c $*.c 

testall: test1 test2 test3 test4 test5

test1: hw11
	./hw11 ./input/in1 construct > construct_out1
	./hw11 ./input/in1 trim > trim_out1
	./hw11 ./input/in1 bst > bst_out1
	diff construct_out1 expected_output/construct_out1
	diff trim_out1 expected_output/trim_out1
	diff bst_out1 expected_output/bst_out1

test2: hw11
	./hw11 ./input/in2 construct > construct_out2
	./hw11 ./input/in2 trim > trim_out2
	./hw11 ./input/in2 bst > bst_out2
	diff construct_out2 expected_output/construct_out2
	diff trim_out2 expected_output/trim_out2
	diff bst_out2 expected_output/bst_out2

test3: hw11
	./hw11 ./input/in3 construct > construct_out3
	./hw11 ./input/in3 trim > trim_out3
	./hw11 ./input/in3 bst > bst_out3
	diff construct_out3 expected_output/construct_out3
	diff trim_out3 expected_output/trim_out3
	diff bst_out3 expected_output/bst_out3

test4: hw11
	./hw11 ./input/in4 construct > construct_out4
	./hw11 ./input/in4 trim > trim_out4
	./hw11 ./input/in4 bst > bst_out4
	diff construct_out4 expected_output/construct_out4
	diff trim_out4 expected_output/trim_out4
	diff bst_out4 expected_output/bst_out4
	
test5: hw11
	./hw11 ./input/in5 construct > construct_out5
	./hw11 ./input/in5 trim > trim_out5
	./hw11 ./input/in5 bst > bst_out5
	diff construct_out5 expected_output/construct_out5
	diff trim_out5 expected_output/trim_out5
	diff bst_out5 expected_output/bst_out5

testmemory: hw11
	valgrind ./hw11 ./input/in1 construct > construct_out1
	valgrind ./hw11 ./input/in1 trim > trim_out1
	valgrind ./hw11 ./input/in1 bst > bst_out1


clean:
	rm -f hw11 *.o bst_out* construct_out* trim_out*