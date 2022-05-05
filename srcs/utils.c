/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:13:08 by ydumaine          #+#    #+#             */
/*   Updated: 2022/05/05 22:25:39 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	b;

	b = 0;
	i = 0;
	s = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s = 1;
		i++;
	}
	while (str [i] >= 48 && str[i] <= 57)
	{
		b = b * 10 - (str[i] - 48);
		i++;
	}
	if (s == 0)
		b = -b;
	return (b);
}

int	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec)
		* 1000 + ((end->tv_usec - start->tv_usec) / 1000));
}

int	ft_clean(t_data *data)
{
	if (data->mutex_fork != NULL)
		free(data->mutex_fork);
	if (data->eat_time != NULL)
		free(data->eat_time);
	if (data->philosophe != NULL)
		free(data->philosophe);
	return (0);
}
