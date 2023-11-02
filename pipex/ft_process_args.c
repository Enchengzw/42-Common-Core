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

static void	*ft_free_triple(char ***pointer)
{
	while (*pointer)
	{
		while (**pointer)
		{
			free(**pointer);
			(*pointer)++;
		}
		free(*pointer);
		pointer++;
	}
	return (0);
}

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

char	***ft_group_cmd(char **argv, int argc)
{
	int		i;
	int		j;
	char	***result;

	j = 0;
	i = 2;
	result = (char ***)malloc(sizeof(char **) * (argc - 2));
	if (!result)
		return (NULL);
	while (i < argc - 1)
	{
		result[j] = ft_split(argv[i], ' ');
		if (!result[j])
			return (ft_free_triple(result));
		j++;
		i++;
	}
	return (result);
}

char	**ft_all_cmd_paths(char ***cmds, char **paths, int argc)
{
	char	**full_paths;
	int		i;

	i = 0;
	full_paths = (char **)malloc(sizeof(char *) * (argc - 2));
	while (cmds[i][0] && i < argc - 1)
	{
		full_paths[i] = ft_cmd_path(cmds[i][0], paths);
		if (!full_paths[i])
			return (ft_free(full_paths));
		i++;
	}
	return (full_paths);
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
	pipe->cmd_args = ft_group_cmd(argv, argc);
	pipe->cmd_paths = ft_all_cmd_paths(pipe->cmd_args, paths, argc);
	pipe->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (pipe);
}
