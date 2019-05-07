/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:07:14 by cpieri            #+#    #+#             */
/*   Updated: 2019/05/06 15:15:04 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	clean_data(t_data **data)
{
	if (*data != NULL)
	{
		if ((*data)->mall == 1)
			ft_memdel((void**)&((*data)->data));
		if ((*data)->data_2_print != NULL)
			ft_memdel((void**)&((*data)->data_2_print));
		ft_memdel((void**)data);
	}
}

void	clean_prog(t_parse *parse)
{
	t_opt	*next;
	t_opt	*lst;

	lst = parse->lst_opts;
	while (lst != NULL)
	{
		if (lst->data->mall == 1)
			ft_memdel((void**)&(lst->data->data));
		if (parse->is_ciphash == e_hash)
			ft_memdel((void**)&(((t_hash*)(lst->data->data_2_print))->h));
		ft_memdel((void**)&(lst->data->data_2_print));
		ft_memdel((void**)&(lst->data));
		next = lst->next;
		ft_memdel((void**)&(lst));
		lst = next;
	}
	parse->lst_opts = NULL;
}