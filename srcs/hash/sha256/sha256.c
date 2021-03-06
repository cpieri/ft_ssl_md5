/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:47:43 by cpieri            #+#    #+#             */
/*   Updated: 2019/04/11 14:12:18 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash/sha256.h"

static void		padding_sha256(t_padding *p, void *data, size_t len)
{
	int		i;

	i = -1;
	p->init_len = len;
	p->nb_bits = len * 8;
	p->new_len = (448 - (p->nb_bits + 1)) % 512;
	p->new_len += p->nb_bits + 64 + 1;
	p->new_len /= 8;
	if (!(p->msg8 = (uint8_t*)ft_memalloc(sizeof(uint8_t) * p->new_len)))
		ft_abort("malloc failed");
	ft_memcpy(p->msg8, data, len);
	p->msg8[len] |= 1 << 7;
	while (++i < 8)
		p->msg8[p->new_len - 8 + i] = ((uint8_t*)&(p->nb_bits))[7 - i];
	p->offest = 0;
}

static uint32_t	*create_w(void *msg_8, size_t offest)
{
	int			i;
	uint32_t	tmp;
	uint32_t	*w;
	uint32_t	s0;
	uint32_t	s1;

	if (!(w = (uint32_t*)ft_memalloc(sizeof(uint32_t) * 64)))
		return (NULL);
	i = -1;
	while (++i < 16)
	{
		ft_memcpy(&(w[i]), msg_8 + offest + (i * 4), sizeof(uint32_t));
		w[i] = swap_uint32t(w[i]);
	}
	while (i < 64)
	{
		tmp = w[i - 15];
		s0 = right_rotate(tmp, 7) ^ right_rotate(tmp, 18) ^ (tmp >> 3);
		tmp = w[i - 2];
		s1 = right_rotate(tmp, 17) ^ right_rotate(tmp, 19) ^ (tmp >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
	return (w);
}

static void		calc_tmp(uint32_t *tmp1, uint32_t *tmp2, t_sha256 *t, int i)
{
	uint32_t	s1;
	uint32_t	s0;
	uint32_t	ch;
	uint32_t	maj;
	uint32_t	t1;

	t1 = t->e;
	s1 = right_rotate(t1, 6) ^ right_rotate(t1, 11) ^ right_rotate(t1, 25);
	ch = ((t->e & t->f) ^ (~(t->e) & t->g));
	*tmp1 = t->h + s1 + ch + g_k_sha256[i] + t->w[i];
	t1 = t->a;
	s0 = right_rotate(t1, 2) ^ right_rotate(t1, 13) ^ right_rotate(t1, 22);
	maj = (t->a & t->b) ^ (t->a & t->c) ^ (t->b & t->c);
	*tmp2 = s0 + maj;
}

static void		calc_sha256(t_sha256 *t)
{
	uint32_t	tmp1;
	uint32_t	tmp2;
	int			i;

	i = -1;
	while (++i < 64)
	{
		calc_tmp(&tmp1, &tmp2, t, i);
		t->h = t->g;
		t->g = t->f;
		t->f = t->e;
		t->e = t->d + tmp1;
		t->d = t->c;
		t->c = t->b;
		t->b = t->a;
		t->a = tmp1 + tmp2;
	}
	t->h0 += t->a;
	t->h1 += t->b;
	t->h2 += t->c;
	t->h3 += t->d;
	t->h4 += t->e;
	t->h5 += t->f;
	t->h6 += t->g;
	t->h7 += t->h;
}

void			*sha256(void *data, size_t len_data)
{
	t_hash		*f_hash;
	t_sha256	t;

	t = (t_sha256){.h0 = SHA256_H0, .h1 = SHA256_H1, .h2 = SHA256_H2,
		.h3 = SHA256_H3, .h4 = SHA256_H4, .h5 = SHA256_H5, .h6 = SHA256_H6,
		.h7 = SHA256_H7, .w = NULL};
	padding_sha256(&(t.p), data, len_data);
	while (t.p.offest < t.p.new_len)
	{
		t.a = t.h0;
		t.b = t.h1;
		t.c = t.h2;
		t.d = t.h3;
		t.e = t.h4;
		t.f = t.h5;
		t.g = t.h6;
		t.h = t.h7;
		t.w = create_w(t.p.msg8, t.p.offest);
		calc_sha256(&t);
		ft_memdel((void**)&(t.w));
		t.p.offest += 64;
	}
	f_hash = set_hash2sha256(&t);
	return (f_hash);
}
