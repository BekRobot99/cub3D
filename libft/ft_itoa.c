/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   	                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:28:56 by abekri            #+#    #+#             */
/*   Updated: 2024/03/14 19:47:31 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_num_length(int n)
{
	int	length;

	length = 1;
	if (n < 0)
		length++;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int		num_length;
	char	*result;

	num_length = ft_get_num_length(n);
	result = (char *)malloc(sizeof(char) * (num_length + 1));
	if (!result)
		return (NULL);
	result += num_length;
	*result-- = '\0';
	*result-- = ft_abs(n % 10) + '0';
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		*result-- = ft_abs(n % 10) + '0';
	}
	if (n < 0)
		*result = '-';
	else
		result++;
	return (result);
}
