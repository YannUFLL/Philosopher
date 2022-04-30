/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compteur.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:06:29 by ydumaine          #+#    #+#             */
/*   Updated: 2022/04/28 15:47:15 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

#define NUM 1000000000

float	time_diff(struct timeval *start, struct timeval *end)
{
	return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void	loopfunc(size_t num)
{
	size_t i;

	i = 0;
	while (i++ < num)
		;
}
int	main(void)
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	loopfunc(NUM);
	gettimeofday(&end, NULL);
	printf("loopfunc(%d) time spent: %0.8f sec\n", NUM, time_diff(&start, &end));
}
