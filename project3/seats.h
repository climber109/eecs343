#include <pthread.h>
#include <semaphore.h>

#ifndef _SEAT_OPERATIONS_H_
#define _SEAT_OPERATIONS_H_

typedef enum
{
    AVAILABLE,
    PENDING,
    OCCUPIED
} seat_state_t;

typedef struct seat_struct
{
    int customer_id;
    seat_state_t state;

    pthread_mutex_t num_readers_lock;
    int num_readers;
    sem_t writer_lock;
} seat_t;


void load_seats(int);
void unload_seats();

void list_seats(char* buf, int bufsize);
void view_seat(char* buf, int bufsize, int seat_num, int customer_num, int customer_priority);
void confirm_seat(char* buf, int bufsize, int seat_num, int customer_num, int customer_priority);
void cancel(char* buf, int bufsize, int seat_num, int customer_num, int customer_priority);

#endif
