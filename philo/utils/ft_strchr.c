/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:30:49 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/15 13:31:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strchr(char *str, int ch)
{
	int	counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] == ch)
			return (str + counter);
		counter++;
	}
	if (str[counter] == ch)
		return (str + counter);
	return (0);
}
