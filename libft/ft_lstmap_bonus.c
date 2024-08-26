/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:28:05 by abekri            #+#    #+#             */
/*   Updated: 2024/03/14 21:21:43 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current_node;
	t_list	*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	tmp = lst;
	new_list = NULL;
	while (tmp != NULL)
	{
		current_node = malloc(sizeof(t_list));
		if (!current_node)
		{
			ft_lstclear(&new_list, del);
			free(current_node);
			return (NULL);
		}
		current_node->content = f(tmp->content);
		current_node->next = NULL;
		ft_lstadd_back(&new_list, current_node);
		tmp = tmp->next;
	}
	free(tmp);
	return (new_list);
}
