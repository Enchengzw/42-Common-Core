/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:15:34 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/25 17:40:50 by ezhou            ###   ########.fr       */
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
	char	**paths;
	int		here_doc;
	char	**cmd_paths;
	char	***cmd_args;
}			t_pipex;

/**
 * @brief Initializes pipex values to 0 or NULL
 * 
 * @return t_pipex* Initialized
 */
t_pipex	*ft_init_pipex(void);
/**
 * @brief Finds PATH directories and splits it into a double pointer
 * 
 * @param env Environmental variables
 * @return char** All path directories listed
 */
char	**ft_find_path(char **env);
void	ft_group_cmd(char **argv, int argc, t_pipex *pipe, int i);
t_pipex	*ft_process_args(char **argv, int argc, t_pipex *pipe, char **env);
void	*ft_full_clear(t_pipex *pipe);
void	*ft_free(char **array);
void	ft_all_cmd_paths(char **paths, int argc, t_pipex *pipe);
int		ft_execute(char **env, t_pipex *pipex, int argc);
int		ft_child_start(t_pipex *pipex, int i, char **env, int fd[2]);
int		ft_child(t_pipex *pipex, int i, char **env, int fd[2]);
int		ft_child_end(t_pipex *pipex, int i, char **env);
char	*ft_process_quotes(char *string, char quote);
char	**ft_split_awk(char const *s, char c);
void	ft_here_doc(int fd, char **argv);
t_pipex	*ft_process_args_hd(char **argv, int argc, t_pipex *pipe, char **env);

#endif