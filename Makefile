all: sthread sthreads

sthread: simplethread.c
        cc -o sthread -lpthread simplethread.c
sthreads: simplethreadSync.c
        cc -o sthreads -lpthread simplethreadSync.c
clean:
        rm *.o *.err
