#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void* display_number(void* arg);

int main() {
    pthread_t tid;
    int num[] = {1, 2, 3, 4, 5};


    for (int i = 0; i < 5; i++) {
        int *n = malloc(sizeof(int));
        *n = num[i];
        pthread_create(&tid, NULL, display_number, (void*)n);
    }

    sleep(5);  // Ensure all threads complete before main exits

    return 0;
}

void* display_number(void* arg) {
    int *N = (int*)arg;
    printf("Number = %d\n", *N);
    free(N);  // Free allocated memory
    return NULL;
}

