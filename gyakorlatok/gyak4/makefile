CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/opt/homebrew/include -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -framework OpenGL -framework GLUT

SRCS = main.c game.c pong.c ball.c pad.c
OBJS = $(SRCS:.c=.o)
TARGET = pong

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)