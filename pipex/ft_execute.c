/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:20:57 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/08 17:35:11 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	ft_child(char *cmd_path, char **cmd, char **env, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd_path, cmd, env);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
		return (EXIT_FAILURE);
}

int	ft_execute(char **env, t_pipex *pipex)
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
		ft_child_process((pipex->cmd_args)[i], (pipex->cmd_args)[i], env, fd);
	}
	return (EXIT_SUCCESS);
}
