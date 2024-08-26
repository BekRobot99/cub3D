/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:27:30 by abekri            #+#    #+#             */
/*   Updated: 2024/03/13 01:45:23 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*object;
	unsigned char	c2bs;

	object = (unsigned char *)s;
	c2bs = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*object == c2bs)
			return (object);
		object++;
		i++;
	}
	return (NULL);
}
