#complier
CC = gcc
#flags
CFLAGS = -Wall -Wextra -g -std=c11

#source
SRCS = main.c fileDat.c crud.c menu.c statistics.c validation.c
#object file
OBJS = $(SRCS:.c=.o)
#output excute
TARGET = student

#default target
all: $(TARGET)

#link objects files to make excutrable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

#compile .c files to -o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# EOF