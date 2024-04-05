/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_last_meal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:00:12 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 14:14:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

void	set_person_meal(t_person *person)
{
	person_meal_lock(person);
	person->last_meal = now();
	person->eat_count += 1;
	person_meal_unlock(person);
}

long long	get_person_meal(t_person *person)
{
	long long	last_meal;

	person_meal_lock(person);
	last_meal = person->last_meal;
	person_meal_unlock(person);
	return (last_meal);
}

void	person_meal_lock(t_person *person)
{
	pthread_mutex_lock(&person->locker);
}

void	person_meal_unlock(t_person *person)
{
	pthread_mutex_unlock(&person->locker);
}

t_person	*person_relise_pair(t_person *person, t_fork_storage *forks)
{
	t_fork_pair	pair;

	pair.left = person->left_fork;
	pair.right = person->right_fork;
	fs_put_pair(person->id, forks, pair);
	person->left_fork = NULL;
	person->right_fork = NULL;
	return (person);
}
