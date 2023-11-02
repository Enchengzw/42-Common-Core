/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:00:18 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/02 17:36:36 by ezhou            ###   ########.fr       */
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
	if (pipe->cmd_paths)
		ft_free(pipe->cmd_paths);
	if (pipe->cmd_args)
	{
		while (*(pipe->cmd_args))
		{
			ft_free(*(pipe->cmd_args));
			(pipe->cmd_args)++;
		}
	}
	free(pipe);
	return (0);
}
