/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:38:24 by brappo            #+#    #+#             */
/*   Updated: 2024/03/19 12:41:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	size_t	length;

	length = 0;
	if (str == NULL)
		return (-1);
	while (str[length])
		length++;
	return (length);
}

int	ft_atoi_unsigned(char *str)
{
	int		length;
	long	result;
	int		index;

	result = 0;
	index = 0;
	length = ft_strlen(str);
	if (length > 10 || length < 0)
		return (-1);
	while (index < length)
	{
		if (str[index] < '0' || str[index] > '9')
			return (-1);
		result = result * 10 + str[index] - '0';
		index++;
	}
	if (result > 2147483647)
		return (-1);
	return (result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*result;
	size_t	index;

	index = 0;
	result = (char *)malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	while (index < nmemb * size)
	{
		result[index] = '\0';
		index++;
	}
	return (result);
}

void	swap_pointers(void ***a, void ***b)
{
	void	**temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
