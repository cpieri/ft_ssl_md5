/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex2char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 21:21:06 by cpieri            #+#    #+#             */
/*   Updated: 2019/05/22 09:46:53 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		calc_nb_len(uint32_t hex)
{
	long	len;

	len = 0;
	if (hex < 16)
		++len;
	while (hex /= 16)
		++len;
	++len;
	return (len);
}

static void	conv_32hexa(char **s, long len_s, uint32_t hex)
{
	uint32_t	nb;
	long		i;
	char		tmp;

	nb = 0;
	i = 0;
	while (i <= len_s)
	{
		nb = hex % 16;
		if (nb < 10)
			(*s)[i] = (nb) % 10 + '0';
		else
			(*s)[i] = (nb) + 'a' - 10;
		if ((i % 2) != 0)
		{
			tmp = (*s)[i];
			(*s)[i] = (*s)[i - 1];
			(*s)[i - 1] = tmp;
		}
		hex /= 16;
		i++;
	}
}

char	*ft_hex2char(uint32_t hex)
{
	char	*s;
	long	len;

	len = calc_nb_len(hex);
	if (!(s = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (hex < 16)
		s[0] = '0';
	conv_32hexa(&s, len - 1, hex);
	return (s);
}
