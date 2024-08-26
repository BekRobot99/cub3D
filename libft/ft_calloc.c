/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:29:33 by abekri            #+#    #+#             */
/*   Updated: 2024/03/15 01:36:19 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	global_size;

	global_size = count * size;
	if (count && size && (global_size) / count != size)
		return (NULL);
	res = (char *)malloc(global_size);
	if (!res)
		return (NULL);
	ft_bzero(res, global_size);
	return ((char *)res);
}
