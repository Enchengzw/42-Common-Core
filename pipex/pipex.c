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
	pipe->here_doc = 0;
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
	int		e_flag;

	e_flag = 0;
	//atexit(leaks);
	pipe = ft_init_pipex();
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		pipe->here_doc = 1;
		pipe = ft_process_args_hd(argv, argc, pipe, env);
	}
	else
		pipe = ft_process_args(argv, argc, pipe, env);
	if (pipe)
		e_flag = ft_execute(env, pipe, argc);
	if (!e_flag && pipe)
		ft_full_clear(pipe);
	return (0);
}
