/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:02:13 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 16:34:14 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

static t_person	*person_eat(t_person *person, t_fork_storage *forks)
{
	print_person_state(person, EATING);
	printf("eat time %d\n", person->last_eat);
	ft_usleep(person->eat_dur);
	fs_put_pair(forks, (t_fork_pair){
		left: person->left_fork,
		right: person->right_fork,
	});
	printf("\t put forks : %d %d\n", person->left_fork->id, person->right_fork->id);
	person->left_fork = NULL;
	person->right_fork = NULL;
	person->eat_count += 1;
	person->last_eat = 0;
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
	t_fork_pair	pair;

	print_person_state(person, THINKING);
	while (1)
	{
		if (person->last_eat >= person->die_time || ps_death_check(person))
			break;
		fs_lock(forks);
		if (fs_check_free_forks(forks))
		{
			pair = fs_take_pair(forks);
			if (pair.left && pair.right)
			{
				person->left_fork = pair.left;
				person->right_fork = pair.right;
				print_person_state(person, TAKE_FORK);
				printf(" forks : %d %d\n", pair.left->id, pair.right->id);
			}
		}
		fs_unlock(forks);
		if (person->left_fork && person->right_fork)
			break ;
		person->last_eat += 10;
		ft_usleep(10);
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
	t_person	*person;

	person = (t_person *)data;
	while (true)
	{
		if ((person->eat_limit != -1
			&& person->eat_count >= person->eat_limit)
			|| ps_death_check(person))
			break ;
		if (person_sleep(person) || ps_death_check(person))
			return (person_die(person));
		if (person_think(person, person->fork_storage) || ps_death_check(person))
			return (person_die(person));
		person_eat(person, person->fork_storage);
		if (ps_death_check(person))
			return (person_die(person));
	}
	return (NULL);
}