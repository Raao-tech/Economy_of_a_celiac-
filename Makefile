CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic -std=c99

TARGET = simulator

SRCS = main.c TADs/Economy.c TADs/Patient.c TADs/Engine.c \
       Src/Engine_reader.c Src/Graphic_engine.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET)

.PHONY: all clean run valgrind