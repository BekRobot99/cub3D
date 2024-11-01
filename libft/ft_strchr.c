/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:43 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 05:12:01 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*haystack;
	char	needle;

	haystack = (char *)str;
	needle = (char)c;
	while (*haystack)
	{
		if (*haystack == needle)
			return (haystack);
		haystack++;
	}
	if (needle == '\0')
	{
		return (haystack);
	}
	return (NULL);
}
