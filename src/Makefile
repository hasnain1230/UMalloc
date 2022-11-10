TARGET = memgrind
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Werror -Wextra -Wundef -Wshadow -Wpointer-arith -O2 -fsanitize=address
OBJ = mymalloc.o $(TARGET).o errors.o

all: $(TARGET)

run: $(TARGET)
	./$<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET).o: $(TARGET).c mymalloc.h
	$(CC) -c $(CFLAGS) $<

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) -c $(CFLAGS) $<

errors.o: errors.c errors.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rfv $(TARGET) *.o *.a *.dylib *.dSYM
