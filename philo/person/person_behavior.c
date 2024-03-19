/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/19 13:04:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static t_person	*person_eat(t_person *person, t_fork_storage *forks)
{
	t_fork_pair	pair;

	person->last_eat = 0;
	print_person_state(person, EATING);
	ft_usleep(person->eat_dur);
	person->last_eat += person->eat_dur;
	pair.left = person->left_fork;
	pair.right = person->right_fork;
	fs_put_pair(forks, pair);
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
	print_person_state(person, THINKING);
	while (1)
	{
		if (person->last_eat >= person->die_time || ps_death_check(person))
			break ;
		fs_lock(forks);
		if (fs_check_free_forks(forks))
			print_person_state(person, TAKE_FORK);
		if (fs_check_free_forks(forks) && !person->left_fork)
			person->left_fork = fs_take_fork(forks);
		else if (fs_check_free_forks(forks) && !person->right_fork)
			person->right_fork = fs_take_fork(forks);
		fs_unlock(forks);
		if (person->left_fork && person->right_fork)
			break ;
		person->last_eat += 1;
		ft_usleep(1);
	}
	if (person->last_eat >= person->die_time)
		return (person);
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
		if (person_eat(person, forks) || ps_death_check(person))
			return (person_die(person));
		if (person_sleep(person) || ps_death_check(person))
			return (person_die(person));
	}
	return (NULL);
}
