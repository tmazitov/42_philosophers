/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:31:55 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/21 18:22:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * (size_t)1000 + time.tv_usec / (size_t)1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = now();
	while ((now() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	diff(size_t t1, size_t t2)
{
	return ((int)(t1 - t2));
}