objects = test.o LLRB.o set.o

example: $(objects)
	cc -o my_set $(objects)

test.o: set.h
set.o: LLRB.h

.PHONY: clean

clean:
	rm my_set $(objects)
