/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:10 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 04:08:41 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!s || !ptr)
		return (NULL);
	i = 0;
	while (i < (ft_strlen((char *)s)))
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
