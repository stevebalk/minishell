#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10

typedef struct {
    char *command;
    char *args[MAX_ARGS];
    char *infile;
    char *outfile;
} Command;

void execute_command(Command cmd, int input_fd, int output_fd) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        //exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execvp(cmd.command, cmd.args);
        perror("execvp"); // execvp only returns on error
        //exit(EXIT_FAILURE);
    }
    // Parent process doesn't wait here; it waits after setting up all commands
}

void run_commands(Command commands[], int n) {
    int input_fd = STDIN_FILENO, output_fd = STDOUT_FILENO, pipe_fds[2], in_fd = STDIN_FILENO;

    for (int i = 0; i < n; ++i) {
        // Setup input redirection
        if (commands[i].infile != NULL) {
            in_fd = open(commands[i].infile, O_RDONLY);
            if (in_fd == -1) {
                perror("open input file");
				continue;
                //exit(EXIT_FAILURE);
            }
            input_fd = in_fd;
        }

        // Setup output redirection or pipe
        if (commands[i].outfile != NULL && in_fd != -1) {  // JJJ in_fd != -1 added to don´t create the out if the in doest exists
            output_fd = open(commands[i].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (output_fd == -1 ) {		
                perror("open output file");
                //exit(EXIT_FAILURE);
            }
        } else if (i < n - 1) {
            // Not the last command, setup pipe
            if (pipe(pipe_fds) == -1) {
                perror("pipe");
                //exit(EXIT_FAILURE);
            }
            output_fd = pipe_fds[1];
        } else {
            output_fd = STDOUT_FILENO;
        }

        execute_command(commands[i], input_fd, output_fd);

        // Close the previous input file descriptor if it was opened
        if (in_fd != STDIN_FILENO) {
            close(in_fd);
            in_fd = STDIN_FILENO;
        }

        // Setup the input for the next command
        if (i < n - 1) {
            close(pipe_fds[1]); // Close the write end of the pipe
            input_fd = pipe_fds[0];
        } else if (input_fd != STDIN_FILENO) {
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO) {
            close(output_fd);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }
}

int main() {
    // Replace with your commands
Command commands[] = {
    { .command = "echo", .args = {"echo", "hello world world world", NULL}, .infile = NULL, .outfile = "out1.txt" } ,
    { .command = "grep", .args = {"grep", "world", NULL}, .infile = "in1.txt", .outfile = "out2.txt" },
    { .command = "wc",  .args = {"wc", "-w", NULL}, .infile = "in2.txt", .outfile = "out3.txt" }
};

    run_commands(commands, 3);

    return 0;
}

