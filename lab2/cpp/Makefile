CC = g++
CFLAGS = -std=c++17

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = tictactoe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
