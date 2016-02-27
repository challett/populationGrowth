CFLAGS= -O2 -DMONITOR
CC=gcc

PROGRAM_NAME= genimg
OBJS = main.c readwriteppm.c fitness.c randimage.c compimage.c mate.c mutate.c

all: omp acc single

clean:
	rm  *.o genimg_omp genimg_acc $(PROGRAM_NAME) *~

omp: $(OBJS)
	$(CC) $(CFLAGS) -fopenmp -o genimg_omp  $?

acc: $(OBJS)
	pgcc $(CFLAGS) -acc -Minfo=accel -o genimg_acc $?

single: $(OBJS)
	$(CC) $(CFLAGS) -o genimg $?
