/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:27:17 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 04:46:57 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s_char;
	char	*d_char;
	size_t	index;

	s_char = (char *)src;
	d_char = (char *)dst;
	index = 0;
	if (d_char < s_char)
	{
		while (index < len)
		{
			d_char[index] = s_char[index];
			index++;
		}
	}
	else
	{
		while (len > 0)
		{
			d_char[len - 1] = s_char[len - 1];
			len--;
		}
	}
	return (dst);
}
