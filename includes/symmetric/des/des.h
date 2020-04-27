/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:13:19 by cpieri            #+#    #+#             */
/*   Updated: 2020/04/24 15:11:05 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "../../../libft/include/libft.h"
# include "../../structure.h"

void	*des(void *opt, size_t len_opt);
void	des_key_schedule(void *key, size_t key_len);

#endif
