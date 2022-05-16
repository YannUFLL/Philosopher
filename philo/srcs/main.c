/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:08:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/16 21:15:46 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h" 

int	ft_check_eat(t_data *data)
{
	if (data->eat_max_enable && data->eat_ok >= (data->nb_philosophers))
	{	
		pthread_mutex_lock(&data->mutex_end);
		data->sim_stop = 1;
		pthread_mutex_unlock(&data->eat_time_edit);
		pthread_mutex_unlock(&data->mutex_end);
		printf("\nAll the philosophers have eaten : %d", data->must_eat);
		return (1);
	}
	return (0);
}

int	ft_check_death(t_data *data, struct timeval time)
{
	int	i;

	i = 0;
	while (i < data->nb_philosophers)
	{
		pthread_mutex_lock(&data->eat_time_edit);
		if (ft_check_eat(data) == 1)
			return (1);
		if (time_diff(&data->eat_time[i], &time) > data->time_to_die)
		{
			pthread_mutex_unlock(&data->eat_time_edit);
			ft_print_msg(data, i, "died");
			pthread_mutex_lock(&data->mutex_end);
			data->sim_stop = 1;
			pthread_mutex_unlock(&data->mutex_end);
			return (1);
		}
		pthread_mutex_unlock(&data->eat_time_edit);
		i++;
	}
	return (0);
}

int	ft_checker(void *ptr)
{
	struct timeval	time;
	t_data			*data;

	data = (t_data *)ptr;
	while (1)
	{
		if (ft_check_eat(data) == 1)
			return (1);
		gettimeofday(&time, NULL);
		if (ft_check_death(data, time) == 1)
		{
			return (0);
		}
	}
}

void	*ft_philosopher(void *ptr)
{
	int				id;
	t_data			*data;
	int				eat_number;
	struct timeval	start;

	eat_number = 0;
	pthread_mutex_lock((&((struct data *)ptr)->take_id));
	data = (t_data *)ptr;
	id = ft_take_id(data);
	gettimeofday(&start, NULL);
	data->eat_time[id] = start;
	if (id % 2 == 0 && data->nb_philosophers % 2 == 1)
		usleep(data->time_to_eat * 1000);
	usleep(id * 100);
	while (1)
	{
		if (!ft_eat(data, id, &eat_number))
			return (0);
		if (!ft_sleep(data, id))
			return (0);
		if (!ft_think(data, id))
			return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (0);
	data.eat_ok = 0;
	pthread_mutex_init(&data.eat_time_edit, NULL);
	if (ft_init_argv(&data, argv, argc) == 1)
		return (ft_clean(&data));
	if (ft_init_philosophers(&data) == 1)
		return (ft_clean(&data));
	ft_checker(&data);
	ft_wait_thread(&data);
	ft_clean(&data);
	return (0);
}
