/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:19 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 03:54:30 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	lsrc;

	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	if (dstsize > 0)
	{
		i = 0;
		while ((size_t)i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (lsrc);
}

// int main()
// {
// 	char src[] = "abekri";
// 	char dest[] = "ae";
// 	printf("%s", ft_strlcpy(dest,src,3));
// }