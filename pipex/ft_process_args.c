/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:15:22 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/31 11:39:30 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static char	*ft_free(char **array)
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

int	ft_count_cmd(char **cmds)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (cmds[i] && cmds[i + 1] != NULL)
	{
		if (cmds[i] != '-')
			counter += 1;
		i++;
	}
	return (counter);
}

char	**ft_group_cmd(char **cmds)
{
	return (0);
}

t_pipex	*ft_process_args(char *cmd_line, t_pipex *pipe)
{
	char	**aux;

	aux = ft_split(cmd_line, ' ');
	pipe->in_fd = open(aux[0], O_RDONLY);
	if ((pipe->in_fd) == -1)
	{
		perror("no such file or directory: ");
		ft_printf("%s\n", aux[0]);
		return (ft_free(aux));
	}
	//ft_group_cmd(aux, pipe);
	return (pipe);
}
