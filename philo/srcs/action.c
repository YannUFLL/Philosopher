/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:14:14 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/14 19:19:02 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_unlock_forks(t_data *data, t_forks *forks)
{
	pthread_mutex_unlock(&data->mutex_fork[forks->fork1]);
	pthread_mutex_unlock(&data->mutex_fork[forks->fork2]);
	return (0);
}

int	ft_sleep(t_data *data, int id)
{
	if (ft_check_stop(data))
		return (0);
	ft_print_msg(data, id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	return (THINK);
}

int	ft_eat(t_data *data, int id, int *eat_number)
{
	struct timeval	start;
	t_forks			forks;

	if (ft_take_forks(data, id, &forks) == 1)
	{
		return (0);
	}
	pthread_mutex_lock(&data->eat_time_edit);
	gettimeofday(&start, NULL);
	data->eat_time[id] = start;
	pthread_mutex_unlock(&data->eat_time_edit);
	if (ft_check_stop(data))
		return (ft_unlock_forks(data, &forks));
	ft_print_msg(data, id, "is eating");
	usleep(data->time_to_eat * 1000 - 5000);
	ft_unlock_forks(data, &forks);
	if (*eat_number == data->must_eat)
	{
		pthread_mutex_lock(&data->eat_time_edit);
		data->eat_ok++;
		pthread_mutex_unlock(&data->eat_time_edit);
	}
	(*eat_number)++;
	return (SLEEP);
}

int	ft_think(t_data *data, int id)
{
	if (ft_check_stop(data))
		return (0);
	ft_print_msg(data, id, "is thinking");
	return (EAT);
}
