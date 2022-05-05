
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:14:19 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/05 19:15:26 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h" 
 
#define sleep 1
#define eat 2
#define think 3

void *ft_checker(void *ptr)
{
	struct timeval time;
	t_data *data;
	data = (t_data *)ptr; 
	int	i;

	i = 0;
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
				printf("\n%d %d is dead",time_diff(&data->start, &time), i);
				pthread_mutex_unlock(&data->mutex_end);
				return (0);
			}
			i++;
		}
	}
}

void	*ft_philosophe(void *ptr)
{
	int id;
	t_data *data;
	int	etat;
	int	eat_number;
	struct timeval start;

	eat_number = 0;
	data = (t_data *)ptr; 
	id = data->philosophe_id;
	gettimeofday(&start, NULL);
	data->eat_time[id] = start;
	data->thread_ready = data->thread_ready + 1;
	etat = eat;
	while (1)
	{
			etat = ft_eat(data, id, &eat_number);
			etat = ft_sleep(data, id);
			etat = ft_think(data, id);
	}
	return (0);
}

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
 
int	ft_init_philosophe(t_data *data, pthread_t *philosophe)
{
	int	i;
	int	rc;

	i = 0;
	while (i < data->nb_philosophe)
	{
		data->philosophe_id = i;
		rc = pthread_create(&philosophe[i], NULL, ft_philosophe, data);
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
	int rc;
	rc = pthread_create(checker, NULL, ft_checker, data);
	if (rc)
		printf("ERROR; return code from pthread_create is %d", rc);
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;
	pthread_t checker;
	if (argc != 5 && argc != 6)
		return (0);
	gettimeofday(&data.start, NULL);
	if (ft_init_argv(&data, argv, argc) == 1)
		return (ft_clean(&data));
	pthread_t philosophe[data.nb_philosophe];
	ft_init_philosophe(&data, &philosophe[0]);
	pthread_mutex_lock(&data.mutex_end);
	ft_init_checker(&data, &checker);
	pthread_mutex_lock(&data.mutex_end);
	//exit(0);
	ft_clean(&data);
	return (0);
}
