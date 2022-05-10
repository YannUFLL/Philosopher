/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:10:26 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/09 20:39:17 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int ft_unlock_forks(t_data *data, t_forks *forks)
{
    pthread_mutex_unlock(&data->mutex_fork[forks->fork1]);
    pthread_mutex_unlock(&data->mutex_fork[forks->fork2]);
    return (0);
}

int	ft_sleep(t_data *data, int id)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
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
	if (ft_check_stop(data))
		return (ft_unlock_forks(data, &forks));
	gettimeofday(&start, NULL);
	pthread_mutex_lock(&data->eat_time_edit);
	data->eat_progress[id] = 1;
	data->eat_time[id] = start;
	pthread_mutex_unlock(&data->eat_time_edit);
	ft_print_msg(data, id, "is eating");
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->eat_time_edit);
	data->eat_time[id] = start;
	data->eat_progress[id] = 0;
	if (*eat_number == data->must_eat)
		data->eat_ok++;
	pthread_mutex_unlock(&data->eat_time_edit);
	(*eat_number)++;
	ft_unlock_forks(data, &forks);
	return (SLEEP);
}

int	ft_think(t_data *data, int id)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	if (ft_check_stop(data))
		return (0);
	ft_print_msg(data, id, "is thinking");
	return (EAT);
}
