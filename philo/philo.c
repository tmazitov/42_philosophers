/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:21:31 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 14:49:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	panic(char *message)
{
	write(2, "Error : ", 8);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (1);
}

static void	run_philosophers(t_state *state)
{
	t_person	**persons;
	t_person	*p;
	int			counter;
	pthread_t	checker_id;

	counter = 0;
	persons = state->persons->persons;
	state->persons->start = now();
	while (persons[counter])
	{
		p = persons[counter];
		set_person_meal(p);
		pthread_create(&p->thread_id, NULL, person_behavior, p);
		counter++;
	}
	pthread_create(&checker_id, NULL, run_person_checker, state->persons);
	pthread_join(checker_id, NULL);
	counter = 0;
	while (persons[counter])
	{
		p = persons[counter];
		pthread_join(p->thread_id, NULL);
		counter++;
	}
}

int	main(int ac, char **av)
{
	t_state			*state;
	t_person_time	time;

	if (ac < 5 || ac > 6)
		return (panic("expected 4 parameters"));
	if (validate(ac, av))
		return (panic("arguments validation failed"));
	state = make_state(av);
	if (!state)
		return (panic("setup program state failed"));
	time.eat_dur = state->time_to_eat;
	time.eat_limit = state->eat_limit;
	time.sleep_dur = state->time_to_sleep;
	time.die_time = state->time_to_die;
	set_time(state->persons, time);
	run_philosophers(state);
	free_state(state);
}
