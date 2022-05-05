/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:08:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/05 22:26:23 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h" 

void	*ft_checker(void *ptr)
{
	struct timeval	time;
	t_data			*data;
	int				i;

	data = (t_data *)ptr;
	while (1)
	{
		gettimeofday(&time, NULL);
		i = 0;
		if (data->eat_ok >= (data->nb_philosophe))
		{
			pthread_mutex_unlock(&data->mutex_end);
			return (0);
		}
		while (i < data->nb_philosophe)
		{
			if (time_diff(&data->eat_time[i], &time) > data->time_to_die)
			{
				printf("\n%d %d is dead", time_diff(&data->start, &time), i);
				pthread_mutex_unlock(&data->mutex_end);
				return (0);
			}
			i++;
		}
	}
}

void	*ft_philosophe(void *ptr)
{
	int				id;
	t_data			*data;
	int				etat;
	int				eat_number;
	struct timeval	start;

	eat_number = 0;
	data = (t_data *)ptr;
	id = data->philosophe_id;
	gettimeofday(&start, NULL);
	data->eat_time[id] = start;
	data->thread_ready = data->thread_ready + 1;
	while (1)
	{
			etat = ft_eat(data, id, &eat_number);
			etat = ft_sleep(data, id);
			etat = ft_think(data, id);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	checker;

	if (argc != 5 && argc != 6)
		return (0);
	gettimeofday(&data.start, NULL);
	if (ft_init_argv(&data, argv, argc) == 1)
		return (ft_clean(&data));
	if (ft_init_philosophe(&data) == 1)
		return (ft_clean(&data));
	pthread_mutex_lock(&data.mutex_end);
	ft_init_checker(&data, &checker);
	pthread_mutex_lock(&data.mutex_end);
	exit(0);
	ft_clean(&data);
	return (0);
}
