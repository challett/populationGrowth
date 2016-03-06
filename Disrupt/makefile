CFLAGS= -O2  -DVIDEO -DDISRUPT #-DMONITOR 
CC=gcc

PROGRAM_NAME= genimg
OBJS = main.c readwriteppm.c fitness.c randimage.c compimage.c mate.c mutate.c rngs.c

all: omp acc single

clean:
	rm  *.o genimg_omp genimg_acc $(PROGRAM_NAME) *~

omp: $(OBJS)
	$(CC) $(CFLAGS) -fopenmp -o genimg_omp  $?

acc: $(OBJS)
	pgcc $(CFLAGS) -acc -Minfo=accel -fast -ta=tesla -Msafeptr  -o genimg_acc  $?

single: $(OBJS)
	$(CC) $(CFLAGS) -o genimg $?
