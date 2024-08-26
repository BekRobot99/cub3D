/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:29:22 by abekri            #+#    #+#             */
/*   Updated: 2024/03/14 19:52:09 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int input)
{
	if ((input >= 65 && input <= 90) || (input >= 97 && input <= 122))
		return (1);
	return (0);
}

// test
// int main(){
//    write(1, ft_isalpha('A') ? "Yes\n" : "No\n", 4);
//    write(1, ft_isalpha('5') ? "Yes\n" : "No\n", 4);
//}