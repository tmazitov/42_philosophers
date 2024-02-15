/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:42:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/15 12:42:53 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	counter;
	int		result;

	counter = 0;
	result = 0;
	while (str1[counter] && str2[counter])
	{
		if (str1[counter] != str2[counter])
		{
			result = (unsigned char)str1[counter]
				- (unsigned char)str2[counter];
			return (result);
		}
		counter++;
	}
	return ((unsigned char)str1[counter] - (unsigned char)str2[counter]);
}
