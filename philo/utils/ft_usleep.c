/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:31:55 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 12:54:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long long	now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	diff(long long t1, long long t2)
{
	return (t1 - t2);
}
