/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:44:22 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/30 11:08:23by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

t_pipex	*ft_init_pipex(void)
{
	t_pipex	*pipe;

	pipe = (t_pipex *)malloc(sizeof(t_pipex));
	pipe->in_fd = 0;
	pipe->out_fd = 0;
	//pipe->here_doc = 0;
	pipe->cmd_paths = NULL;
	pipe->paths = NULL;
	pipe->cmd_args = NULL;
	return (pipe);
}

void	leaks()
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipe;
	pid_t	pid;
	int		i;
	int		fd[2];

	i = 0;
	atexit(leaks);
	pipe = ft_init_pipex();
	pipe = ft_process_args(argv, argc, pipe, env);
	ft_execute(env, pipe, argc);
	ft_full_clear(pipe);
	return (0);
}
