#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t seconds_elapsed = 0;
volatile sig_atomic_t got_sigint = 0;

void alarm_handler(int signum) {
    seconds_elapsed++;
    alarm(1);
}

void sigint_handler(int signum) {
    got_sigint = 1;
}

int main(void) {
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal SIGALRM");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal SIGINT");
        exit(EXIT_FAILURE);
    }

    alarm(1);

    while (!got_sigint) {
        pause();
    }

    printf("\nProgram ran for %d second%s.\n", (int)seconds_elapsed,
           (seconds_elapsed == 1) ? "" : "s");

    return 0;
}
