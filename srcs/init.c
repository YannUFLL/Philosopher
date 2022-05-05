/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:19:42 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/05 22:24:57 by ydumaine         ###   ########.fr       */
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
	data->is_dead = 0;
	data->thread_ready = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philosophe);
	data->eat_time = malloc(sizeof(struct timeval) * data->nb_philosophe);
	if (data->mutex_fork == NULL || data->eat_time == NULL)
		return (1);
	while (i < data->nb_philosophe)
		pthread_mutex_init(&data->mutex_fork[i++], NULL);
	pthread_mutex_init(&data->mutex_end, NULL);
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
	while (i < data->nb_philosophe)
	{
		data->philosophe_id = i;
		rc = pthread_create(&data->philosophe[i], NULL, ft_philosophe, data);
		if (rc)
		{
			printf("ERROR; return code from pthread_create is %d", rc);
			break ;
		}
		while (data->thread_ready != i)
			;
		i++;
	}
	return (0);
}

int	ft_init_checker(t_data *data, pthread_t *checker)
{
	int	rc;

	rc = pthread_create(checker, NULL, ft_checker, data);
	if (rc)
		printf("ERROR; return code from pthread_create is %d", rc);
	return (0);
}