/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:14:34 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:15:46 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*pointer;

	pointer = (char *)malloc(sizeof(char) * size);
	if (!pointer)
		return (NULL);
	ft_memset(pointer, '\0', size);
	return (pointer);
}

int	ft_number_length(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		counter += 1;
	if (n < 0)
		counter += 1;
	while (n != 0)
	{
		n = n / 10;
		counter += 1;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*list;
	int		length;
	long	ln;

	ln = n;
	length = ft_number_length(n);
	list = ft_strnew(length + 1);
	if (!list)
		return (NULL);
	if (ln < 0)
	{
		ln *= -1;
		list[0] = '-';
	}
	if (ln == 0)
		list[length - 1] = '0';
	list[length] = '\0';
	while (ln != 0)
	{
		list[length - 1] = ln % 10 + '0';
		length--;
		ln /= 10;
	}
	return (list);
}
/*
int	main(void)
{
	char	*str;

	str = ft_itoa(0);
	printf("%s\n", str);
	return (0);
}
*/