/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:27:21 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 01:15:17 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_char;
	const char		*s_char;

	d_char = (unsigned char *)dst;
	s_char = (const char *)src;
	if (!d_char && !s_char)
		return (NULL);
	i = 0;
	while (i < n)
	{
		d_char[i] = s_char[i];
		i++;
	}
	return (dst);
}

//int main(){
//  char d_char[] = "";
//  char s_src[] = "42 Heilbronn";
//  printf("%s",ft_memcpy(d_char,src_char,5));
//}