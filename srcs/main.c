/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:03:04 by ydumaine          #+#    #+#             */
/*   Updated: 2022/04/30 02:18:19 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h" 
 
 
#define sleep 1
#define eat 2
#define think 3

int	ft_start_action(int ph_id)
{
	if (ph_id / 3 == 0)
		return (eat);
	else if (ph_id % 3 == 1)
		return (think);
	else 
		return (sleep);
}


int	time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec - start->tv_usec));
}

int	ft_check_death(t_data *data, struct timeval *eat_time)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (time_diff(eat_time, &time) > data->time_to_die)
		return (1);
	else 
		return (0);
}

int	ft_take_foork(t_data *data, int id, struct timeval *eat_time)
{
	int	foork1_ok;
	int foork2_ok;
	int	foork1_id;
	int	foork2_id;

	foork1_ok = 0;
	foork2_ok = 0;
	if ((id + 1) > (data->nb_philosophe - 1))
		foork1_id = 0; 
	else 
		foork1_id = id + 1;
	if ((id - 1) < 0)
		foork2_id = (data->nb_philosophe - 1);
	else 
		foork1_id = id + 1;
	while (foork1_ok == 0 && foork2_ok == 0)
	{
		if (ft_check_death(data, eat_time))
			return (1);
		if (foork1_ok == 0 && pthread_mutex_lock(&data->mutex_fork[foork1_id]) == 0)
			foork1_ok = 1;
		if (foork2_ok == 0 && pthread_mutex_lock(&data->mutex_fork[foork2_id]) == 0)
			foork2_ok = 1;
	}
	return (0);
}

int	ft_sleep(t_data *data, int id, struct timeval *eat_time)
{
	struct timeval start;
	struct timeval end; 

	gettimeofday(&start, NULL);
	printf("%d %d is sleeping", time_diff(&data->start, &start), id);
	while (time_diff(&start, &end) < data->time_to_sleep)
	{
		usleep(10);
		gettimeofday(&end, NULL);
	if (ft_check_death(data, eat_time))
		return (0);
	}
	return (think);
}


int	ft_eat(t_data *data, int id, struct timeval *eat_time)
{
	struct timeval start;
	struct timeval end; 

	if (ft_take_foork(data, id, eat_time) == 1)
		return (0);
	gettimeofday(&start, NULL);
	printf("%d %d is eating",time_diff(&data->start, &start), id);
	while (time_diff(&start, &end) < data->time_to_eat)
	{
		usleep(10);
		gettimeofday(&end, NULL);
		if (ft_check_death(data, eat_time))
			return (0); 
	}
	return (sleep);
}

int	ft_think(t_data *data, int id, struct timeval *eat_time)
{
	struct timeval start;
	struct timeval end; 
	
	gettimeofday(&start, NULL);
	printf("%d %d is thinking",time_diff(&data->start, &start), id);
	return (eat);
}

void	*ft_philosophe(void *ptr)
{
	int id;
	t_data *data;
	data = (t_data *)ptr; 
	int	etat;
	struct timeval eat_time;

	id = data->philosophe_id;
	etat = ft_start_action(id);
	gettimeofday(&eat_time, NULL);
	while (1)
	{
		if (etat == sleep)
			etat = ft_sleep(data, id, &eat_time);
		if (etat == think)
			etat = ft_think(data, id, &eat_time) ;
		if (etat == eat)
			etat = ft_eat(data, id, &eat_time);
			gettimeofday(&eat_time, NULL);
		if (etat == 0)
			break; 
	}
	gettimeofday(&eat_time, NULL);
	printf("%d %d is dead",time_diff(&data->start, &eat_time), id);
	return (NULL);
}

void	ft_init_argv(t_data *data, char **argv)
{
	data->nb_philosophe = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = ft_atoi(argv[5]);
}
 
int	ft_init_philosophe(t_data *data, pthread_t *philosophe)
{
	int	i;
	int ctrl; 
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
		i++;
	}
	while (1)
		;
	return (0);
}

int main(int argc, char **argv)
{
	int i = 0;
	int ret = 0;
	t_data data;
	pthread_mutex_t mutex_fork[data.nb_philosophe];

	gettimeofday(&data.start, NULL);
	data.mutex_fork = &mutex_fork[0];
	ft_init_argv(&data, argv);
	pthread_t philosophe[data.nb_philosophe];
	ft_init_philosophe(&data, &philosophe[0]);
	return (0);
}
