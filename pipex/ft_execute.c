/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:20:57 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/16 16:54:53 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	ft_child_start(t_pipex *pipex, int i, char **env, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipex->in_fd, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve((pipex->cmd_paths)[i], (pipex->cmd_args)[i], env) == -1)
		{
			perror("execve error");
			return (EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_execute(char **env, t_pipex *pipex, int argc)
{
	int	fd[2];
	int	i;

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		return (EXIT_FAILURE);
	}
	i = -1;
	while ((pipex->cmd_args)[++i])
	{
		if (i == 0)
			ft_child_start(pipex, i, env, fd);
		else if (i == (argc - 2))
			ft_child_end(pipex, i, env, fd);
		else
			ft_child(pipex, i, env, fd);
	}
	return (EXIT_SUCCESS);
}
