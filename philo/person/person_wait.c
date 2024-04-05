/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:17:21 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 14:51:42 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static int	person_waiter(t_person *person, int time)
{
	long long	start;

	start = now();
	usleep(time * 900);
	while (diff(now(), start) < time)
	{
		usleep(100);
		if (is_not_ok(person))
			return (1);
	}
	return (0);
}

int	person_wait(t_person *person, t_person_state state)
{
	int	wait_time;

	if (state == SLEEPING)
		wait_time = person->sleep_dur;
	else if (state == EATING)
		wait_time = person->eat_dur;
	else if (state == DIE)
		wait_time = person->die_time;
	else
		return (0);
	return (person_waiter(person, wait_time));
}

static int	left_id(t_person *person, t_fork_storage *forks)
{
	if (forks->amount % 2 == 0 && person->id == forks->amount)
		return (1);
	else
		return (person->id);
}

static int	right_id(t_person *person, t_fork_storage *forks)
{
	if (forks->amount % 2 == 0 && person->id == forks->amount)
		return (person->id);
	else if (person->id == forks->amount)
		return (1);
	return (person->id + 1);
}

int	person_wait_pair(t_person *person, t_fork_storage *forks)
{
	int			left_fork_id;
	int			right_fork_id;

	left_fork_id = left_id(person, forks);
	right_fork_id = right_id(person, forks);
	fs_lock(forks);
	if (fork_is_mine(forks, right_fork_id, person->id) 
		|| fork_is_mine(forks, left_fork_id, person->id))
		return (fs_unlock(forks), 1);
	fs_unlock(forks);
	if (forks->amount % 2 != 0 && person->id == forks->amount)
	{
		person->right_fork = fs_take_fork(forks, right_fork_id);
		person->left_fork = fs_take_fork(forks, left_fork_id);
	}
	else
	{
		person->left_fork = fs_take_fork(forks, left_fork_id);
		person->right_fork = fs_take_fork(forks, right_fork_id);
	}
	fs_lock(forks);
	person->left_fork->last_owner = person->id;
	person->right_fork->last_owner = person->id;
	fs_unlock(forks);
	return (0);
}
