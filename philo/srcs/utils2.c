/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:16:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/16 19:52:31 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_print_msg(t_data *data, int id, char *msg)
{
	struct timeval	time;

	pthread_mutex_lock(&data->mutex_end);
	gettimeofday(&time, NULL);
	if (data->sim_stop != 1)
	{
		pthread_mutex_unlock(&data->mutex_end);
		printf("\n%d %d %s", time_diff(&data->start, &time), id + 1, msg);
		return (0);
	}
	pthread_mutex_unlock(&data->mutex_end);
	return (0);
}

int	ft_take_id(t_data *data)
{
	int	id;

	id = data->philosopher_id;
	data->philosopher_id = data->philosopher_id + 1;
	pthread_mutex_unlock(&data->take_id);
	pthread_mutex_lock(&data->start_sim);
	pthread_mutex_unlock(&data->start_sim);
	return (id);
}

int	time_diff_us(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec)
		* 1000000 + ((end->tv_usec - start->tv_usec)));
}

void	ft_usleep(int us)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	while (time_diff_us(&start, &end) < us)
	{
		gettimeofday(&end, NULL);
		usleep(500);
	}
}
