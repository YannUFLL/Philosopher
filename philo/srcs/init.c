/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:19:42 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/16 19:53:28 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_argv(t_data *data, char **argv, int argc)
{
	int	i;

	i = 0;
	data->mutex_fork = NULL;
	data->eat_time = NULL;
	data->nb_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->sim_stop = 0;
	data->eat_max_enable = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (argc == 6)
		data->eat_max_enable = 1;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philosophers);
	data->eat_time = malloc(sizeof(struct timeval) * data->nb_philosophers);
	if (data->mutex_fork == NULL || data->eat_time == NULL)
		return (1);
	while (i < data->nb_philosophers)
		pthread_mutex_init(&data->mutex_fork[i++], NULL);
	pthread_mutex_init(&data->mutex_end, NULL);
	pthread_mutex_init(&data->take_id, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	return (0);
}

int	ft_init_philosophers(t_data *data)
{
	int			i;
	int			rc;

	data->philosopher = NULL;
	data->philosopher = malloc(sizeof(pthread_t) * data->nb_philosophers);
	if (data->philosopher == NULL)
		return (1);
	i = 0;
	data->philosopher_id = 0;
	pthread_mutex_init(&data->start_sim, NULL);
	pthread_mutex_lock(&data->start_sim);
	while (i < data->nb_philosophers)
	{
		rc = pthread_create(&data->philosopher[i], NULL, ft_philosopher, data);
		if (rc)
		{
			printf("ERROR; return code from pthread_create is %d", rc);
			break ;
		}
		i++;
	}
	gettimeofday(&data->start, NULL);
	pthread_mutex_unlock(&data->start_sim);
	return (0);
}
