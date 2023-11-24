/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:00:18 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/20 14:10:21 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	*ft_free(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
	return (NULL);
}

void	*ft_full_clear(t_pipex *pipe)
{
	int	i;

	i = -1;
	if (pipe)
	{
		if (pipe->cmd_paths)
			ft_free(pipe->cmd_paths);
		if (pipe->cmd_args)
		{
			while ((pipe->cmd_args)[++i])
				ft_free((pipe->cmd_args)[i]);
			free(pipe->cmd_args);
		}
		if (pipe->paths)
			ft_free(pipe->paths);
		if (pipe->in_fd > 0)
			close(pipe->in_fd);
		if (pipe->out_fd > 0)
			close(pipe->in_fd);
		free(pipe);
	}
	return (0);
}
