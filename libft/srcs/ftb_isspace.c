/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftb_isspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:45:00 by tmilon            #+#    #+#             */
/*   Updated: 2017/11/29 16:50:20 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ftb_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r')
		return (1);
	return (0);
}
