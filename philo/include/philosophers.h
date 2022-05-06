/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:05:26 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/05 22:24:34 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define THINK 3

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

# define SLEEP 1
# define EAT 2
# define THINK 3

typedef struct data
{
	int				nb_philosophe;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				is_dead;
	int				philosophe_id;
	int				thread_ready;
	int				eat_ok;
	struct timeval	*eat_time;
	struct timeval	start;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_end;
	pthread_t		*philosophe;
}			t_data;

typedef struct forks
{
	int	fork1;
	int	fork2;
}	t_forks;

int		ft_init_argv(t_data *data, char **argv, int argc);
int		ft_init_philosophe(t_data *data);
int		ft_init_checker(t_data *data, pthread_t *checker);
int		ft_atoi(const char *str);
int		time_diff(struct timeval *start, struct timeval *end);
int		ft_clean(t_data *data);
int		ft_take_forks(t_data *data, int id, t_forks *forks);
int		ft_sleep(t_data *data, int id);
int		ft_eat(t_data *data, int id, int *eat_number);
int		ft_think(t_data *data, int id);
int		ft_atoi(const char *str);
void	*ft_philosophe(void *ptr);
int		ft_init_checker(t_data *data, pthread_t *checker);
void	*ft_checker(void *ptr);
#endif 
