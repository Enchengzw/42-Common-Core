/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:18:49 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/25 14:36:55 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static char	*ft_strcpy(char *dst, const char *src, size_t start, size_t end)
{
	size_t	s_index;
	size_t	d_index;

	s_index = 0;
	d_index = 0;
	if (!dst || !src)
		return (0);
	while (src[s_index])
	{
		if (s_index != start && s_index != end)
		{
			dst[d_index] = src[s_index];
			d_index++;
		}
		s_index++;
	}
	dst[d_index] = '\0';
	return (dst);
}

int	ft_strchrindex(char *s, int c)
{
	int	index;

	index = 0;
	if (!s || *s == 0)
		return (0);
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (0);
}

int	ft_strrchrindex(const char *s, int c)
{
	size_t	index;

	index = ft_strlen(s);
	while (s[index] != (unsigned char)c && index > 0)
	{
		index--;
	}
	if (s[index] == (unsigned char)c)
		return (index);
	else
		return (0);
}

char	*ft_process_quotes(char *string, char quote)
{
	int		start;
	int		end;
	int		length;
	char	*new;

	start = ft_strchrindex(string, quote);
	end = ft_strrchrindex(string, quote);
	length = ft_strlen(string);
	new = (char *)malloc(sizeof(char) * (length - 2));
	if (!new)
		return (NULL);
	new = ft_strcpy(new, string, start, end);
	return (new);
}
/*
int main(int argc, char **argv)
{
	char	*test;
	char **dict;

	test = ft_process_quotes(argv[1], '\'');
	ft_printf("%s\n", test);
	ft_printf("%s\n", argv[1]);
	return (0);
}
*/