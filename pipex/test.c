#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	write_hello(int fd[2])
{
	close(fd[0]);
	write(fd[1], "hello", 6);
}

int	main(int argc, char **argv)
{	
	/*int fd = open("texto.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	int fd2 = open("resultado.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	close(fd);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);*/
	printf("%s\n", argv[1]);
	char *awk_args[] = { "awk", "{printf(\"%s\", \"Hola\")}" , "texto.txt", NULL };
	//char *awk_args[] = { "awk", argv[1], "texto.txt", NULL };
	// Specify the path to the awk executable
	//char *awk_path = "/usr/bin/awk";

	// Execute the awk command using execve
	/*if (execve(awk_path, awk_args, NULL) == -1)
	{
		perror("execve");
		return (1);
	}*/

	// This code will not be reached if execve is successful
	return (0);
}