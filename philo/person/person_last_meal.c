/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   person_last_meal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:00:12 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/26 16:57:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "person.h"

void	set_person_meal(t_person *person)
{
	person_meal_lock(person);
	person->last_meal = now();
	person_meal_unlock(person);
}

size_t	get_person_meal(t_person *person)
{
	size_t	last_meal;

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
