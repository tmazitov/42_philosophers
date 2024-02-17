/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:49:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/02/17 16:10:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_num_overflow(char *num)
{
	char	*check_num;
	int		num_value;
	int		result;

	num_value = ft_atoi(num);
	check_num = ft_itoa(num_value);
	if (!check_num)
		return (1);
	result = ft_strcmp(num, check_num);
	free(check_num);
	return (result);
}

static int	check_all_num_overflow(char **nums)
{
	int	counter;

	counter = 0;
	while (nums[counter])
	{
		if (check_num_overflow(nums[counter]))
			return (1);
		counter++;
	}
	return (0);
}	

static int	fill_state(t_state	*state, char **av)
{
	if (check_all_num_overflow(av+1))
		return (1);
	state->philo_amount = ft_atoi(av[1]);
	if (state->philo_amount <= 0)
		return (1);
	state->time_to_die = ft_atoi(av[2]);
	if (state->time_to_die <= 0)
		return (1); 
	state->time_to_eat = ft_atoi(av[3]);
	if (state->time_to_die <= 0)
		return (1); 
	state->time_to_sleep = ft_atoi(av[4]);
	if (state->time_to_die <= 0)
		return (1); 
	if (av[5]) 
	{
		state->eat_limit = ft_atoi(av[5]);
		if (state->eat_limit < 0)
			return (1);
	}
	else
		state->eat_limit = -1;
	return (0);
}

t_state	*make_state(char **av)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->forks = NULL;
	state->persons = NULL;
	if (fill_state(state, av))
		return (free_state(state));
	state->forks = make_fork_storage(state->philo_amount);
	if (!state->forks)
		return (free_state(state));
	state->persons = make_person_storage(state->philo_amount);
	if (!state->persons)
		return (free_state(state));
	set_time(state->persons, (t_person_time){
		eat_dur: state->time_to_eat,
		eat_limit: state->eat_limit,
		sleep_dur: state->time_to_sleep,
		die_time: state->time_to_die,
	});
	set_forks(state->persons, state->forks);
	return (state);
}

void	*free_state(t_state *state)
{
	if (!state)
		return (NULL);
	if (state->forks)
		free_fork_storage(state->forks);
	if (state->persons)
		free_person_storage(state->persons);
	free(state);
	return (NULL);
}
