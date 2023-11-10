# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

void	write_hello(int fd[2])
{
	close(fd[0]);
	write(fd[1], "hello", 6);
}

int main() {
    // Command to execute: awk '{disk_t += $3} END {printf ("%d\n"), disk_t}' /path/to/input_file.txt
    char *awk_args[] = { "awk", "{disk_t += $3} END {printf (\"%d\\n\"), disk_t}", "texto.txt", NULL };

    // Specify the path to the awk executable
    char *awk_path = "/usr/bin/awk";

    // Execute the awk command using execve
    if (execve(awk_path, awk_args, NULL) == -1) {
        perror("execve");
        return 1;
    }

    // This code will not be reached if execve is successful
    return 0;
}