# Hasnain Ali (ha430)
# Rushabh Patel (rsp155)
# Della Maret (dm1379)
# iLab Machine Tested On: ilab.cs.rutgers.edu and rlab1.cs.rutgers.edu

TARGET = memgrind
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Wextra -Wundef -Wshadow -Wpointer-arith -O3 -fsanitize=address
OBJ = umalloc.o $(TARGET).o errors.o

LONG_TEST = 0

all: $(TARGET)

long_test:
	$(MAKE) LONG_TEST=1

run: $(TARGET)
	./$<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET).o: $(TARGET).c umalloc.h # If LONG_TEST is equal to 1, then the long test is run
ifeq ($(LONG_TEST), 1)
	$(CC) $(CFLAGS) -DLONG_TEST -c $<
else
	$(CC) $(CFLAGS) -c $<
endif

umalloc.o: umalloc.c umalloc.h
	$(CC) -c $(CFLAGS) $<

errors.o: errors.c errors.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rfv $(TARGET) *.o *.a *.dylib *.dSYM
