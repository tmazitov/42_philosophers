/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 17:05:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static t_person	*person_eat(t_person *person)
{
	t_fork_pair	pair;

	set_person_meal(person);
	if (print_person_state(person, EATING))
		return (NULL);
	ft_usleep(person->eat_dur);
	pair.left = person->left_fork;
	pair.right = person->right_fork;
	fs_put_pair(pair);
	person->left_fork = NULL;
	person->right_fork = NULL;
	person->eat_count += 1;
	return (NULL);
}

static t_person	*person_sleep(t_person *person)
{
	if (print_person_state(person, SLEEPING))
		return (NULL);
	ft_usleep(person->sleep_dur);
	return (NULL);
}

static int	is_not_ok(t_person *person)
{
	int	value;
	t_person_storage *storage;

	storage = (t_person_storage*)person->storage;
	ps_lock(storage);
	value = storage->dead_log;
	ps_unlock(storage);
	return (value);
}

static t_person	*person_think(t_person *person, t_fork_storage *forks)
{	
	int			left_fork_id;
	int			right_fork_id;

	if (forks->amount == 1)
		return (person);
	if (print_person_state(person, THINKING))
		return (person);
	left_fork_id = person->id;
	if (person->id == forks->amount)
		right_fork_id = 1;
	else
		right_fork_id = left_fork_id + 1;
	if (forks->amount % 2 == 0 && person->id == forks->amount)
	{
		right_fork_id = person->id;
		left_fork_id = 1;
	}
	person->left_fork = fs_take_fork(forks, left_fork_id);
	person->right_fork = fs_take_fork(forks, right_fork_id);
	if (is_not_ok(person))
		return (NULL);
	if (print_person_state(person, TAKE_FORK))
		return (NULL);
	if (print_person_state(person, TAKE_FORK))
		return (NULL);
	return (NULL);
}

void	*person_behavior(void *data)
{
	t_person			*person;
	t_fork_storage		*forks;

	person = (t_person *)data;
	forks = person->fork_storage;
	set_person_meal(person);
	if (person->id % 2 == 0)
		ft_usleep(person->eat_dur);
	while (true)
	{
		if ((person->eat_limit != -1
			&& person->eat_count >= person->eat_limit)
			|| is_not_ok(person))
			break ;
		if (person_think(person, forks) || is_not_ok(person))
			return (NULL);
		if (person_eat(person) || is_not_ok(person))
			return (NULL);
		if (person_sleep(person) || is_not_ok(person))
			return (NULL);
	}
	return (NULL);
}
