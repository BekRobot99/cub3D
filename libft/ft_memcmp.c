/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:27:26 by abekri            #+#    #+#             */
/*   Updated: 2024/03/12 17:55:19 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*arg1;
	unsigned char	*arg2;

	i = 0;
	arg1 = (unsigned char *)s1;
	arg2 = (unsigned char *)s2;
	while (i < n)
	{
		if (arg1[i] != arg2[i])
			return (arg1[i] - arg2[i]);
		i++;
	}
	return (0);
}
