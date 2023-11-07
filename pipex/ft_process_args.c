/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:15:22 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/02 18:15:32 by ezhou            ###   ########.fr       */
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
	if (!aux)
		return (NULL);
	ft_strlcpy(aux + 1, cmd, length + 1);
	aux[0] = '/';
	r_path = NULL;
	while (path[i])
	{
		free(r_path);
		r_path = ft_strjoin(path[i], aux);
		if (!r_path)
			return (ft_clean(aux));
		if (access(r_path, F_OK) == 0)
			return (free(aux), r_path);
		i++;
	}
	free(aux);
	return (0);
}

void	ft_group_cmd(char **argv, int argc, t_pipex *pipe)
{
	int		i;
	int		j;

	j = 0;
	i = 2;
	pipe->cmd_args = (char ***)malloc(sizeof(char **) * (argc - 2));
	if (!(pipe->cmd_args))
		return ;
	while (i < argc - 1)
	{
		(pipe->cmd_args)[j] = ft_split(argv[i], ' ');
		if (!(pipe->cmd_args)[j])
		{
			ft_full_clear(pipe);
			return ;
		}
		j++;
		i++;
	}
}

void	ft_all_cmd_paths(char **paths, int argc, t_pipex *pipe)
{
	int		i;

	i = 0;
	pipe->cmd_paths = (char **)malloc(sizeof(char *) * (argc - 2));
	while ((pipe->cmd_args)[i][0] && i < argc - 1)
	{
		(pipe->cmd_paths)[i] = ft_cmd_path((pipe->cmd_args)[i][0], paths);
		if (!(pipe->cmd_paths)[i])
		{
			ft_full_clear(pipe);
			return ;
		}
		i++;
	}
}

t_pipex	*ft_process_args(char **argv, int argc, t_pipex *pipe, char **paths)
{
	pipe->in_fd = open(argv[1], O_RDONLY);
	if ((pipe->in_fd) == -1)
	{
		perror("no such file or directory: ");
		ft_printf("%s\n", argv[1]);
		return (NULL);
	}
	ft_group_cmd(argv, argc, pipe);
	ft_all_cmd_paths(paths, argc, pipe);
	pipe->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (pipe);
}
