/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:05:26 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/05 16:19:37 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct data
{
	int	nb_philosophe; 
	int	time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	is_dead;
	int	philosophe_id;
	int	thread_ready;
	int	eat_ok;
	struct timeval *eat_time;
	struct timeval start;
   	pthread_mutex_t *mutex_fork;
	pthread_mutex_t mutex_end;	
}			t_data;

typedef struct forks
{
	int	fork1;
	int	fork2;
}	t_forks; 

int	ft_atoi(const char *str);

#endif 
