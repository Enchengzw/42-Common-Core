/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_awk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:31:36 by ezhou             #+#    #+#             */
/*   Updated: 2024/02/28 18:07:41 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static char	**ft_free_dict(char **array)
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

int static	ft_count_word(char const *s, char c)
{
	int	index;
	int	count;

	if (*s != c && *s != '\0')
		count = 1;
	else
		count = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1])
			count += 1;
		index++;
	}
	return (count);
}

int static	ft_strlen_char(char const *s, char c)
{
	int	index;

	index = 0;
	while (s[index] && s[index] != c)
		index++;
	return (index);
}

char static	*ft_new_word(char const *s, char c, char *array_cell, int *index)
{
	int	length;
	int	one;
	int	two;

	one = ft_strchrindex((char *)s, '\'');
	two = ft_strchrindex((char *)s, ' ');
	if (ft_strcontains((char *)s, '\'') && one < two)
	{
		length = ft_strrchrindex((char *)s, '\'') + 1;
		array_cell = ft_strtrim(s, "\'");
		if (!array_cell)
			return (NULL);
	}
	else
	{
		length = ft_strlen_char(s, c);
		array_cell = (char *)malloc(sizeof(char) * (length + 1));
		if (!array_cell)
			return (NULL);
		ft_strlcpy(array_cell, s, length + 1);
	}
	*index += length - 1;
	return (array_cell);
}

char	**ft_split_awk(char const *s, char c)
{
	int		index;
	char	**array;
	int		array_index;

	index = -1;
	array_index = 0;
	array = (char **)ft_calloc(sizeof(char *), (ft_count_word(s, c) + 1));
	if (!array)
		return (NULL);
	while (s[++index])
	{
		if (s[index] != c)
		{
			array[array_index] = ft_new_word(&(s[index]), c, array[array_index],
					&index);
			if (!array[array_index])
				return (ft_free_dict(array));
			array_index++;
		}
	}
	array[array_index] = NULL;
	return (array);
}
