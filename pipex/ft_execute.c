/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:31:13 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/27 16:31:15 by ezhou            ###   ########.fr       */
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
			ft_putstr_fd("Error executing execve\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_child(t_pipex *pipex, int i, char **env, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (execve((pipex->cmd_paths)[i], (pipex->cmd_args)[i], env) == -1)
		{
			ft_putstr_fd("Error executing execve\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_child_end(t_pipex *pipex, int i, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->out_fd, STDOUT_FILENO);
		if (execve((pipex->cmd_paths)[i], (pipex->cmd_args)[i], env) == -1)
		{
			ft_putstr_fd("Error executing execve\n", 2);
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
	int	flag;

	flag = 0;
	i = -1;
	while ((pipex->cmd_args)[++i])
	{
		if (pipe(fd) == -1 || i > (argc - 2))
		{
			ft_putstr_fd("Error creating the pipe\n", 2);
			return (EXIT_FAILURE);
		}
		if (i == 0)
			flag = ft_child_start(pipex, i, env, fd);
		else if (!((pipex->cmd_args)[i + 1]))
			flag = ft_child_end(pipex, i, env);
		else
			flag = ft_child(pipex, i, env, fd);
		if (flag)
			return (ft_full_clear(pipex), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
