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

    alarm(5);
}

int main(void) {
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    alarm(5);

    while (1) {
        if (alarm_received) {
            printf("Turing was right!\n");
            fflush(stdout);
            alarm_received = 0;
        }
        sleep(1);
    }

    return 0;
}
