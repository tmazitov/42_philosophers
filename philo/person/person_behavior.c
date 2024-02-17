/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 12:52:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static void	person_eat(t_person *person, t_fork_storage *forks)
{
	(void)forks;
	print_person_state(person, EATING);
	usleep(person->eat_dur);
	person->eat_count += 1;
	person->last_eat = 0;
}

static void	person_sleep(t_person *person)
{
	print_person_state(person, SLEEPING);
	usleep(person->sleep_dur);
	person->last_eat += person->sleep_dur;
}

static void	person_think(t_person *person, t_fork_storage *forks)
{
	print_person_state(person, THINKING);
	while (check_free_forks(forks) == false)
	{
		person->last_eat += 10;
		if (person->last_eat >= person->die_time)
			return ;
		usleep(10);
	}
}

static void	*person_die(t_person *person)
{
	return (print_person_state(person, DIE), person);
}

void	*person_behavior(void *data)
{
	t_person	*person;

	person = (t_person *)data;
	while (true)
	{
		if (person->eat_limit != -1 && person->eat_count >= person->eat_limit)
			return (NULL);
		person_sleep(person);
		if (person->last_eat >= person->die_time)
			return (person_die(person));
		person_think(person, person->fork_storage);
		if (person->last_eat >= person->die_time)
			return (person_die(person));
		person_eat(person, person->fork_storage);
	}
	return (NULL);
}