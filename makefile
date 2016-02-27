CFLAGS= -pg -O2 -Wall -DMONITOR
CC=gcc

PROGRAM_NAME= genimg
OBJS = main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o

$(PROGRAM_NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $? -lgomp

clean:
	rm  *.o $(PROGRAM_NAME) *~
