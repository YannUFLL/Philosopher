/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:19:42 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/09 19:00:54 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_argv(t_data *data, char **argv, int argc)
{
	int	i;

	i = 0;
	data->mutex_fork = NULL;
	data->eat_time = NULL;
	data->nb_philosophe = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->sim_stop = 0;
	data->eat_max_enable = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (argc == 6)
		data->eat_max_enable = 1;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philosophe);
	data->eat_time = malloc(sizeof(struct timeval) * data->nb_philosophe);
	if (data->mutex_fork == NULL || data->eat_time == NULL)
		return (1);
	while (i < data->nb_philosophe)
		pthread_mutex_init(&data->mutex_fork[i++], NULL);
	pthread_mutex_init(&data->mutex_end, NULL);
	pthread_mutex_init(&data->print_msg, NULL);
	pthread_mutex_init(&data->take_id, NULL);
	return (0);
}

int	ft_init_philosophe(t_data *data)
{
	int			i;
	int			rc;

	data->philosophe = NULL;
	data->philosophe = malloc(sizeof(pthread_t) * data->nb_philosophe);
	if (data->philosophe == NULL)
		return (1);
	i = 0;
	data->philosophe_id = 0;
	while (i < data->nb_philosophe)
	{
		rc = pthread_create(&data->philosophe[i], NULL, ft_philosophe, data);
		if (rc)
		{
			printf("ERROR; return code from pthread_create is %d", rc);
			break ;
		}
		i++;
	}
	return (0);
}
