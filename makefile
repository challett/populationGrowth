CFLAGS=-g -O2 -Wall -DMONITOR


PROGRAM_NAME= genimg
OBJS = main.o readwriteppm.o fitness.o randimage.o compimage.o mate.o mutate.o

$(PROGRAM_NAME): $(OBJS)
	$(CC) -o $@ $? -lgomp

clean:
	rm  *.o $(PROGRAM_NAME) *~
