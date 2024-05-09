/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:09:15 by abchikhi          #+#    #+#             */
/*   Updated: 2024/05/09 10:09:16 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*allocate_buffer(long long *number, int *len, int *neg)
{
	char	*res;

	if (*number < 0)
	{
		*neg = 1;
		(*len) += 1;
		*number *= -1;
	}
	res = malloc(sizeof(char) * (*len + 1));
	return (res);
}

static void	fill_string(long long number, int len, int neg, char *string)
{
	string[len--] = '\0';
	if (number <= 9)
		string[len--] = number + 48;
	else
	{
		while (len >= 0)
		{
			string[len--] = (number % 10) + 48;
			number /= 10;
		}
	}
	if (neg)
		string[0] = '-';
}

char	*ft_itoa(int n)
{
	int			len;
	char		*res;
	int			neg;
	long long	number;

	len = ft_intlen(n);
	neg = 0;
	number = (long long)n;
	if (number == 0)
		return ((char *)ft_strdup("0"));
	res = allocate_buffer(&number, &len, &neg);
	if (!res)
		return (NULL);
	fill_string(number, len, neg, res);
	return (res);
}
