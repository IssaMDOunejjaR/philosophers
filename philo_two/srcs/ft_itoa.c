/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:38:32 by iounejja          #+#    #+#             */
/*   Updated: 2021/05/30 18:30:36 by iounejja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	len_number(long int nb)
{
	int		l;

	l = 0;
	if (nb == 0)
		l = 1;
	else
	{
		if (nb < 0)
		{
			nb = -nb;
			l++;
		}
		while (nb > 0)
		{
			nb /= 10;
			l++;
		}
	}
	return (l);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		count;
	char	*str;

	nb = n;
	count = len_number(nb);
	str = malloc(sizeof(char) * (count + 1));
	str[count--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[count--] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
