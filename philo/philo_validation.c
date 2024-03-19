/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:22:37 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/19 13:10:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_number(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter]) 
	{
		if (!ft_isdigit(str[counter]))
			return (0);
		counter++;
	}
	return (1);
}

int	validate(int ac, char **av)
{
	char	**arguments;
	int		counter;

	if (ac != 5)
		return (0);
	arguments = av + 1;
	counter = 0;
	while (arguments[counter])
	{
		if (!check_number(arguments[counter]))
			return (1);
		counter++;
	}
	return (0);
}
