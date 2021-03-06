/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishexa_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:49:31 by cpieri            #+#    #+#             */
/*   Updated: 2018/01/22 15:09:12 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ishexa_color(char *s)
{
	int		i;

	i = 3;
	if (s[1] != '0' && s[2] != 'x')
		return (0);
	while (i <= 8)
	{
		if (s[i] < 48 && s[i] > 57 && s[i] < 'A' && s[i] > 'F')
			return (0);
		i++;
	}
	return (1);
}
