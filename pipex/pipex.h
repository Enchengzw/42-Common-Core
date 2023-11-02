/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:15:34 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/02 18:10:42 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	//int		here_doc;
	char	**cmd_paths;
	char	***cmd_args;
}			t_pipex;

t_pipex	*ft_init_pipex(void);
char	**ft_find_path(char **env);
char	***ft_group_cmd(char **argv, int argc);
t_pipex	*ft_process_args(char **argv, int argc, t_pipex *pipe, char **paths);
void	*ft_full_clear(t_pipex *pipe);
void	*ft_free(char **array);
char	**ft_all_cmd_paths(char ***cmds, char **paths, int argc);

#endif