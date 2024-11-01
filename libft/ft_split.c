/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:21:18 by sdukic            #+#    #+#             */
/*   Updated: 2024/03/15 06:18:56 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen1(const char *str, char c)
{
	int	length;

	length = 0;
	while (str[length] && str[length] != c)
	{
		length++;
	}
	return (length);
}

static int	count_strings(const char *str, char c)
{
	int	count;
	int	len;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		len = ft_strlen1(str, c);
		str += len;
		if (len > 0)
			count++;
	}
	return (count);
}

static char	*ft_strdup1(const char *src, int len)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

static int	ft_free_memory(int index, char **strings)
{
	while (index >= 0)
		free(strings[index--]);
	free(strings);
	return ('\0');
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		quentity_of_strings;
	int		i;
	int		str_len;

	quentity_of_strings = count_strings(s, c);
	res = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < quentity_of_strings)
	{
		while (*s && *s == c)
			s++;
		str_len = ft_strlen1(s, c);
		res[i] = ft_strdup1(s, str_len);
		if (!res[i])
		{
			ft_free_memory(i, res);
			return (NULL);
		}
		s += str_len;
	}
	res[quentity_of_strings] = 0;
	return (res);
}
