/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:38:28 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/30 15:51:30 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	*ft_cmd_path(char *cmd, char **path)
{
	char	*r_path;
	int		i;
	int		length;
	char	*aux;

	length = ft_strlen(cmd);
	i = 0;
	aux = (char *)malloc(sizeof(char) * length + 2);
	ft_strlcpy(aux + 1, cmd, length + 1);
	aux[0] = '/';
	r_path = NULL;
	while (path[i])
	{
		free(r_path);
		r_path = ft_strjoin(path[i], aux);
		if (access(r_path, F_OK) == 0)
		{
			free(aux);
			return (r_path);
		}
		i++;
	}
	free(aux);
	return (0);
}
