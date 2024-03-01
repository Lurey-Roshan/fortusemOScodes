#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> // header file for sleep ;Provides access to the POSIX operating system API, including sleep.gcc
#include<pthread.h>
// a normal C function that is executed as thread
// when its name is specified in pthread_create(0)

void *myThreadFun(void *vargp){
    sleep(3);
    printf("Printing hello from thread");
     sleep(3);

    return NULL;

}
int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id,NULL);
    printf("\nAfter Thread\n");
    exit(0);

}