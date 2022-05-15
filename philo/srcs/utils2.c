/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:16:34 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/14 17:58:59 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_print_msg(t_data *data, int id, char *msg)
{
    struct timeval  time;
	pthread_mutex_lock(&data->mutex_end);
    if (data->sim_stop == 1)
	{
		pthread_mutex_unlock(&data->mutex_end);
        return (0);
	}
	pthread_mutex_unlock(&data->mutex_end);
	gettimeofday(&time, NULL);
	printf("\n%d %d %s", time_diff(&data->start, &time), id + 1, msg);
	return (0);
}
