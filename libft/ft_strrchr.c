/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:25:48 by abekri            #+#    #+#             */
/*   Updated: 2024/03/14 03:12:22 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		haystack_length;
	const char	*last_character;

	haystack_length = ft_strlen(str);
	last_character = str + haystack_length;
	while (haystack_length-- + 1)
	{
		if (*last_character == (char)c)
			return ((char *)last_character);
		last_character--;
	}
	return (NULL);
}
