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
	pipe->is_invalid_infile = 0;
	pipe->cmd_paths = NULL;
	pipe->cmd_args = NULL;
	return (pipe);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipe;

	pipe = ft_init_pipex();
	pipe->cmd_paths = ft_find_path(env);
	(void)argc;
	(void)argv;

	return (0);
}
