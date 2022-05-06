/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:14:22 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/06 11:05:53 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_lock_pair(t_data *data, t_forks *forks, int id)
{
	struct timeval	time;

	pthread_mutex_lock(&data->mutex_fork[forks->fork1]);
	gettimeofday(&time, NULL);
	printf("\n%d %d has taken a fork", time_diff(&data->start, &time), id + 1);
	pthread_mutex_lock(&data->mutex_fork[forks->fork2]);
	gettimeofday(&time, NULL);
	printf("\n%d %d has taken a fork", time_diff(&data->start, &time), id + 1);
	return (0);
}

int	ft_lock_impair(t_data *data, t_forks *forks, int id)
{
	struct timeval	time;

	pthread_mutex_lock(&data->mutex_fork[forks->fork2]);
	gettimeofday(&time, NULL);
	printf("\n%d %d has taken a fork", time_diff(&data->start, &time), id + 1);
	pthread_mutex_lock(&data->mutex_fork[forks->fork1]);
	gettimeofday(&time, NULL);
	printf("\n%d %d has taken a fork", time_diff(&data->start, &time), id + 1);
	return (0);
}

int	ft_take_forks(t_data *data, int id, t_forks *forks)
{
	if (id == data->nb_philosophe - 1)
	{
		forks->fork1 = id;
		forks->fork2 = 0;
	}
	else
	{
		forks->fork1 = id;
		forks->fork2 = id + 1;
	}
	if (id % 2 == 0)
		return (ft_lock_pair(data, forks, id));
	else if (id % 2 == 1)
		return (ft_lock_impair(data, forks, id));
	return (0);
}
