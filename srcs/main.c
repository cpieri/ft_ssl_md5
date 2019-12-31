/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:05:16 by cpieri            #+#    #+#             */
/*   Updated: 2020/01/02 11:00:17 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		main(int ac, char **av)
{
	t_parse	parse;

	if (ac < 2)
		print_usage(1, NULL);
	parse = parsing(ac, av);
	dispatch(&parse);
	// clean_prog(&parse);
	return (0);
}
