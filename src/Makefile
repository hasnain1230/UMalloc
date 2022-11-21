TARGET = test
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wvla -Wextra -Wundef -Wshadow -Wpointer-arith -fsanitize=address
OBJ = umalloc.o $(TARGET).o errors.o

all: $(TARGET)

run: $(TARGET)
	./$<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET).o: $(TARGET).c umalloc.h
	$(CC) -c $(CFLAGS) $<

umalloc.o: umalloc.c umalloc.h
	$(CC) -c $(CFLAGS) $<

errors.o: errors.c errors.h
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rfv $(TARGET) *.o *.a *.dylib *.dSYM
