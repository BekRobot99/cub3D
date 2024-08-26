/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:26:40 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 01:37:41 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dup;
	size_t	i;

	size = 1;
	while (s1[size - 1] != '\0')
		size++;
	dup = malloc(size);
	i = 0;
	while (i < size && dup != NULL)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}

/* #include <stdio.h>

int	main(void)
{
	char	str[] = "Test";
	char	*dup = ft_strdup(str);
	str[0] = 'W';
	printf("%s", dup);
	return (0);
} */