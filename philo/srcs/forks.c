/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:14:22 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/10 22:27:10 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_lonely(t_data *data)
{
	if (data->nb_philosophe == 1)
	{
		while (1) 
		{
			pthread_mutex_lock(&data->mutex_end);
			if (data->sim_stop == 1)
			{
				pthread_mutex_unlock(&data->mutex_end);
				return (1);
			}
			else 
				pthread_mutex_unlock(&data->mutex_end);
		}
	}
	return (0);
}

int	ft_lock_pair(t_data *data, t_forks *forks, int id)
{
	pthread_mutex_lock(&data->mutex_fork[forks->fork1]);
	ft_print_msg(data, id, "has taken a fork");
	if (ft_check_stop(data))
	{
        pthread_mutex_unlock(&data->mutex_fork[forks->fork1]);
		return (1);
	}
	if (ft_lonely(data) == 1)
		return (1);
	pthread_mutex_lock(&data->mutex_fork[forks->fork2]);
	ft_print_msg(data, id, "has taken a fork");
	if (ft_check_stop(data))
	{
        ft_unlock_forks(data, forks);
		return (1);
	}
	return (0);
}

int	ft_lock_impair(t_data *data, t_forks *forks, int id)
{
	pthread_mutex_lock(&data->mutex_fork[forks->fork2]);
	ft_print_msg(data, id, "has taken a fork");
	if (ft_check_stop(data))
	{
        pthread_mutex_unlock(&data->mutex_fork[forks->fork2]);
		return (1);
	}
	if (ft_lonely(data) == 1)
		return (1);
	pthread_mutex_lock(&data->mutex_fork[forks->fork1]);
	ft_print_msg(data, id, "has taken a fork");
	if (ft_check_stop(data))
	{
        ft_unlock_forks(data, forks);
		return (1);
	}
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
