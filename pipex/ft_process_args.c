/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:15:22 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/27 16:27:49 by ezhou            ###   ########.fr       */
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
	i = -1;
	aux = (char *)malloc(sizeof(char) * length + 2);
	if (!aux)
		return (NULL);
	ft_strlcpy(aux + 1, cmd, length + 1);
	aux[0] = '/';
	r_path = NULL;
	while (path[++i])
	{
		free(r_path);
		r_path = ft_strjoin(path[i], aux);
		if (!r_path)
			return (ft_clean(aux));
		if (access(r_path, F_OK) == 0 && access(r_path, X_OK) == 0)
			return (free(aux), r_path);
	}
	free(aux);
	free(r_path);
	return (0);
}

int	ft_group_cmd(char **argv, int argc, t_pipex *pipe, int i)
{
	int		j;
	char	*string;
	int		flag;

	flag = 0;
	j = 0;
	pipe->cmd_args = (char ***)malloc(sizeof(char **) * (argc - 2));
	if (!(pipe->cmd_args))
		return (EXIT_FAILURE);
	while (i < argc - 1)
	{
		string = argv[i];
		if (ft_strcontains(string, '\''))
			string = ft_process_quotes(string, '\'', &flag);
		if (ft_strcontains(string, '\"'))
			string = ft_process_quotes(string, '\"', &flag);
		(pipe->cmd_args)[j++] = ft_split_awk(string, ' ');
		if (flag)
			free(string);
		if (!(pipe->cmd_args)[j - 1])
			return (ft_full_clear(pipe), EXIT_FAILURE);
		i++;
	}
	(pipe->cmd_args)[j] = NULL;
	return (EXIT_SUCCESS);
}

int	ft_all_cmd_paths(char **paths, int argc, t_pipex *pipe)
{
	int		i;

	i = 0;
	pipe->cmd_paths = (char **)malloc(sizeof(char *) * (argc - 2));
	while (i < (argc - 1) && (pipe->cmd_args)[i])
	{
		(pipe->cmd_paths)[i] = ft_cmd_path((pipe->cmd_args)[i][0], paths);
		if (!(pipe->cmd_paths)[i])
		{
			ft_printf("The command doesn't exist\n");
			ft_full_clear(pipe);
			return (1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

t_pipex	*ft_process_args(char **argv, int argc, t_pipex *pipe, char **env)
{
	int	flag;

	flag = 0;
	if (argc < 5)
	{
		ft_putstr_fd("Input arguments error\n", 2);
		return (NULL);
	}
	pipe->paths = ft_find_path(env);
	if (!(pipe->paths))
		return (0);
	pipe->in_fd = open(argv[1], O_RDONLY);
	if ((pipe->in_fd) == -1)
	{
		ft_putstr_fd("Error opening the infile", 2);
		return (NULL);
	}
	flag = ft_group_cmd(argv, argc, pipe, 2);
	if (flag)
		return (0);
	flag = ft_all_cmd_paths(pipe->paths, argc, pipe);
	if (flag)
		return (0);
	pipe->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (pipe);
}

t_pipex	*ft_process_args_hd(char **argv, int argc, t_pipex *pipe, char **env)
{
	int	flag;

	flag = 0;
	if (argc < 5 || (pipe->here_doc && argc < 6))
	{
		ft_putstr_fd("Input arguments error\n", 2);
		return (NULL);
	}
	pipe->paths = ft_find_path(env);
	if (!(pipe->paths))
		return (0);
	pipe->in_fd = open(argv[1], O_RDONLY | O_WRONLY | O_CREAT, 0666);
	if ((pipe->in_fd) == -1)
		return (ft_putstr_fd("Error opening the file", 2), NULL);
	flag = ft_here_doc(pipe->in_fd, argv);
	if (flag)
		return (0);
	flag = ft_group_cmd(argv, argc, pipe, 3);
	if (flag)
		return (0);
	flag = ft_all_cmd_paths(pipe->paths, argc, pipe);
	if (flag)
		return (0);
	pipe->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (pipe);
}
