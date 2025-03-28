/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:30:42 by hadia             #+#    #+#             */
/*   Updated: 2025/03/28 16:31:16 by hadia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_atoi_base(char *str, int base)
{
	int result;
	int sign;
	int i;

	result = 0;
	sign = 1;
	i = 0;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * base + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * base + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * base + (str[i] - 'a' + 10);
		else
			break ;
		i++;
	}
	return (result * sign);
}