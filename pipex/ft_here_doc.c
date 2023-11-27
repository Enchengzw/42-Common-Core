/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:40:10 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/27 16:27:24 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	ft_here_doc(int fd, char **argv)
{
	char	*input;
	char	*string;

	string = ft_strjoin(argv[2], "\n");
	if (!string)
		return (EXIT_FAILURE);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		input = get_next_line(0);
		if (ft_strncmp(string, input, ft_strlen(input)) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		ft_clean(input);
	}
	free(input);
	free(string);
	return (EXIT_SUCCESS);
}
