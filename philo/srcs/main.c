/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:08:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/10 16:56:55 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h" 

int	ft_init_eatprogress(t_data *data)
{
	int	i;

	i = 0;
	data->eat_progress = malloc(sizeof(int) * data->nb_philosophe);
	if (data->eat_progress == NULL)
		return (1);
	while (i < data->nb_philosophe)
		data->eat_progress[i++] = 0;
	return (0);
}

int	ft_check_death(t_data *data, struct timeval time)
{
	int	i;

	i = 0;
	while (i < data->nb_philosophe)
	{
		pthread_mutex_lock(&data->eat_time_edit);
		if (time_diff(&data->eat_time[i], &time) > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_msg);
			if (data->eat_progress[i] == 0)
			{
				pthread_mutex_unlock(&data->eat_time_edit);
				printf("\n%d %d died", time_diff(&data->start, &time), i + 1);
				pthread_mutex_unlock(&data->print_msg);
				pthread_mutex_lock(&data->mutex_end);
				data->sim_stop = 1;
				pthread_mutex_unlock(&data->mutex_end);
				return (1);
			}
			pthread_mutex_unlock(&data->print_msg);
		}
		i++;
		pthread_mutex_unlock(&data->eat_time_edit);
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
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&data->eat_time_edit);
		if (data->eat_max_enable && data->eat_ok >= (data->nb_philosophe))
		{	
			pthread_mutex_unlock(&data->eat_time_edit);
			pthread_mutex_lock(&data->mutex_end);
			data->sim_stop = 1;
			pthread_mutex_unlock(&data->mutex_end);
			return (0);
		}
		pthread_mutex_unlock(&data->eat_time_edit);
		if (ft_check_death(data, time) == 1)
		{
			return (0);
		}
	}
}

void	*ft_philosophe(void *ptr)
{
	int				id;
	t_data			*data;
	int				eat_number;
	struct timeval	start;

	eat_number = 0;
	data = (t_data *)ptr;
	pthread_mutex_lock(&data->take_id);
	id = data->philosophe_id;
	data->philosophe_id = data->philosophe_id + 1;
	pthread_mutex_unlock(&data->take_id);
	gettimeofday(&start, NULL);
	data->eat_time[id] = start;
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
	gettimeofday(&data.start, NULL);
	data.eat_ok = 0;
	pthread_mutex_init(&data.eat_time_edit, NULL);
	data.eat_progress = NULL;
	if (ft_init_argv(&data, argv, argc) == 1)
		return (ft_clean(&data));
	if (ft_init_eatprogress(&data) == 1)
		return (ft_clean(&data));
	if (ft_init_philosophe(&data) == 1)
		return (ft_clean(&data));
	ft_checker(&data);
	ft_wait_thread(&data);
	ft_clean(&data);
	return (0);
}
