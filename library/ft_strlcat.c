/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:27 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 01:30:13 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	d_len;
	unsigned int	s_len;
	unsigned int	offset;
	unsigned int	ind;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	offset = d_len;
	ind = 0;
	if (dstsize == 0)
		return (s_len);
	while ((src[ind] != '\0') && (ind + offset < (dstsize - 1)))
	{
		dst[ind + offset] = src[ind];
		ind++;
	}
	if (ind < dstsize)
		dst[ind + offset] = '\0';
	if (d_len > dstsize)
		return (s_len + dstsize);
	return (d_len + s_len);
}
