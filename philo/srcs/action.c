/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:10:26 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/06 16:58:27 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(t_data *data, int id)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	pthread_mutex_lock(&data->print_msg);
	printf("\n%d %d is sleeping", time_diff(&data->start, &start), id + 1);
	pthread_mutex_unlock(&data->print_msg);
	usleep(data->time_to_sleep * 1000);
	return (THINK);
}

int	ft_eat(t_data *data, int id, int *eat_number)
{
	struct timeval	start;
	t_forks			forks;

	ft_take_forks(data, id, &forks);
	pthread_mutex_lock(&data->eat_time_edit);
	pthread_mutex_unlock(&data->eat_time_edit);
	pthread_mutex_lock(&data->print_msg);
	gettimeofday(&start, NULL);
	data->eat_progress[id] = 1;
	data->eat_time[id] = start;
	printf("\n%d %d is eating", time_diff(&data->start, &start), id + 1);
	pthread_mutex_unlock(&data->print_msg);
	usleep(data->time_to_eat * 1000);
	gettimeofday(&start, NULL);
	pthread_mutex_lock(&data->eat_time_edit);
	data->eat_time[id] = start;
	data->eat_progress[id] = 0;
	pthread_mutex_unlock(&data->eat_time_edit);
	if (*eat_number == data->must_eat)
		data->eat_ok++;
	(*eat_number)++;
	pthread_mutex_unlock(&data->mutex_fork[forks.fork1]);
	pthread_mutex_unlock(&data->mutex_fork[forks.fork2]);
	return (SLEEP);
}

int	ft_think(t_data *data, int id)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	pthread_mutex_lock(&data->print_msg);
	printf("\n%d %d is thinking", time_diff(&data->start, &start), id + 1);
	pthread_mutex_unlock(&data->print_msg);
	return (EAT);
}
