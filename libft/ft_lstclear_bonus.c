/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:28:40 by abekri            #+#    #+#             */
/*   Updated: 2024/03/14 21:00:35 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*count;

	count = *lst;
	if (!*lst || !(*del))
		return ;
	while (count)
	{
		temp = count;
		count = count->next;
		(*del)(temp->content);
		free(temp);
	}
	*lst = NULL;
}
