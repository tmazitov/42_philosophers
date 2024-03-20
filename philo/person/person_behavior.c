/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 14:47:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static t_person	*person_eat(t_person *person)
{
	t_fork_pair	pair;

	person->last_eat = 0;
	print_person_state(person, EATING);
	ft_usleep(person->eat_dur);
	person->last_eat += person->eat_dur;
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
	print_person_state(person, SLEEPING);
	ft_usleep(person->sleep_dur);
	person->last_eat += person->sleep_dur;
	if (person->last_eat >= person->die_time)
		return (person);
	return (NULL);
}

static t_person	*person_think(t_person *person, t_fork_storage *forks)
{	
	int			left_fork_id;
	int			right_fork_id;
	long long	start;
	
	if (forks->amount == 1)
		return (person);
	print_person_state(person, THINKING);
	left_fork_id = person->id;
	if (person->id == forks->amount)
		right_fork_id = 1;
	else
		right_fork_id = person->id + 1;
	if (forks->amount % 2 == 0 && person->id % 2 == 0)
	{
		right_fork_id = person->id;
		left_fork_id = person->id - 1;
	}
	start = get_current_time();
	person->left_fork = fs_take_fork(forks, left_fork_id);
	if ((int)(get_current_time() - start) > 0)
		person->last_eat += (int)(get_current_time() - start);
	if (person->last_eat >= person->die_time || ps_death_check(person))
		return (person);
	print_person_state(person, TAKE_FORK);
	
	start = get_current_time();
	person->right_fork = fs_take_fork(forks, right_fork_id);
	if ((int)(get_current_time() - start) > 0)
		person->last_eat += (int)(get_current_time() - start);
	if (person->last_eat >= person->die_time || ps_death_check(person))
		return (person);
	print_person_state(person, TAKE_FORK);
	return (NULL);
}

static void	*person_die(t_person *person)
{
	if (ps_death_check(person) == false)
	{
		ps_death_set(person);
		print_person_state(person, DIE);
		return (person);
	}
	return (NULL);
}

void	*person_behavior(void *data)
{
	t_person		*person;
	t_fork_storage	*forks;

	person = (t_person *)data;
	forks = person->fork_storage;
	if (person->id % 2 == 0)
	{
		person->last_eat = person->eat_dur;
		ft_usleep(person->eat_dur);
	}
	while (true)
	{
		if ((person->eat_limit != -1
				&& person->eat_count >= person->eat_limit)
			|| ps_death_check(person))
			break ;
		if (person_think(person, forks) || ps_death_check(person))
			return (person_die(person));
		if (person_eat(person) || ps_death_check(person))
			return (person_die(person));
		if (person_sleep(person) || ps_death_check(person))
			return (person_die(person));
	}
	return (NULL);
}
