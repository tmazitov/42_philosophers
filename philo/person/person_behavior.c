/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/20 19:45:14 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static t_person	*person_eat(t_person *person)
{
	t_fork_pair	pair;

	person->last_eat += person->eat_dur;
	if (print_person_state(person, EATING))
		return (NULL);
	ft_usleep(person->eat_dur);
	if (person->last_eat >= person->die_time)
		return (person);
	pair.left = person->left_fork;
	pair.right = person->right_fork;
	fs_put_pair(pair);
	person->left_fork = NULL;
	person->right_fork = NULL;
	person->eat_count += 1;
	person->last_eat = 0;
	return (NULL);
}

static t_person	*person_sleep(t_person *person)
{
	if (print_person_state(person, SLEEPING))
		return (NULL);
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
	// size_t		start;
	
	if (forks->amount == 1)
		return (person);
	if (print_person_state(person, THINKING))
		return (person);
	left_fork_id = person->id;
	if (person->id == forks->amount)
		right_fork_id = 1;
	else
		right_fork_id = person->id + 1;
	if (forks->amount % 2 == 0 && person->id == forks->amount)
	{
		right_fork_id = person->id;
		left_fork_id = 1;
	}
	// start = now();
	person->left_fork = fs_take_fork(forks, left_fork_id);;
	if (ps_death_check(person))
		return (NULL);
	if (print_person_state(person, TAKE_FORK))
		return (NULL);
	person->right_fork = fs_take_fork(forks, right_fork_id);
	if (ps_death_check(person))
		return (NULL);
	if (print_person_state(person, TAKE_FORK))
		return (NULL);
	// printf("last eat %d + %d\n", person->last_eat, (int)(now() - start));
	// person->last_eat += (int)(now() - start);
	// if (person->last_eat >= person->die_time)
	// 	return (person);
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
	person->last_eat = 0;
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
