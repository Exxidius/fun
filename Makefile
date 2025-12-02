CC = gcc

CFLAGS = -Wall
LDFLAGS = -lncurses

SRC = src/*.c
OUT = fun

all: $(OUT)

$(OUT): $(SRC)
		$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
		rm $(OUT)

