#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarm_received = 0;

void alarm_handler(int signum) {
    const char *msg = "Hello World!\n";
    write(STDOUT_FILENO, msg, 13);
    alarm_received = 1; 
}

int main(void) {
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    alarm(5);

    while (!alarm_received) {
        sleep(1);
    }

    printf("Turing was right!\n");

    return 0;
}
