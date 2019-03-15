/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:46:37 by cpieri            #+#    #+#             */
/*   Updated: 2019/03/15 15:57:23 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha_2.h"
#include <stdio.h>

const uint32_t g_k_sha256[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void				padding_sha256(t_padding *p, void *data, size_t len_d)
{
	int		i;

	i = -1;
	p->init_len = len_d;
	p->nb_bits = len_d * 8;
	p->new_len = (448 - (p->nb_bits + 1)) % 512;
	p->new_len += p->nb_bits + 64 + 1;
	p->new_len /= 8;
	if (!(p->str_bits = (uint8_t*)ft_memalloc(sizeof(uint8_t) * p->new_len)))
		ft_abort("lol");
	ft_memcpy(p->str_bits, data, len_d);
	p->str_bits[len_d] |= 1 << 7;
	while (++i < 8)
		p->str_bits[p->new_len - 8 + i] = ((uint8_t*)&(p->nb_bits))[7 - i];
	ft_membits(p->str_bits, p->new_len, sizeof(uint8_t));
	p->offest = 0;
}

static t_sha256_utils	operates_sha256(t_sha256 *s, int i)
{
	t_sha256_utils		tool;
	uint32_t			e;
	uint32_t			a;

	a = s->a;
	e = s->e;
	tool.s1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
	//ft_membits(&(tool.s1),0,sizeof(uint32_t));
	tool.ch = (s->e & s->f) ^ ((~s->e) & s->g);
	tool.tmp1 = s->h + tool.s1 + tool.ch + g_k_sha256[i] + s->w[i];
	tool.s0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
	tool.maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
	tool.tmp2 = tool.s0 + tool.maj;
	return (tool);
}

static void				calc_sha256(t_sha256 *e)
{
	int				i;
	t_sha256_utils	tool;

	i = -1;
	while (++i < 64)
	{
		tool = operates_sha256(e, i);
		e->h = e->g;
		e->g = e->f;
		e->f = e->e;
		e->e = e->d + tool.tmp1;
		e->d = e->c;
		e->c = e->b;
		e->b = e->a;
		e->a = tool.tmp1 + tool.tmp2;
		//printf("%x\n",e->a);
	}
}

static uint32_t			*set_w_sha256(uint8_t *data, size_t offest)
{
	uint32_t	*w;
	uint32_t	s0;
	uint32_t	tmp;
	uint32_t	s1;
	int			i;

	i = -1;
	if (!(w = (uint32_t*)ft_memalloc(sizeof(uint32_t) * 64)))
	{
		ft_memdel((void**)&w);
		ft_abort("lol");
	}
	while (++i < 16)//{
		ft_memcpy(&w[i], data + offest + (i * 4), sizeof(uint32_t));
	//ft_membits(&w[i],0,sizeof(uint32_t));}
	while (i < 64)
	{
		tmp = w[i - 15];
		s0 = right_rotate(tmp, 7) ^ right_rotate(tmp, 18) ^ (tmp >> 3);
		tmp = w[i - 2];
		s1 = right_rotate(tmp, 17) ^ right_rotate(tmp, 19) ^ (tmp >> 10);
		w[i] = s1 + w[i - 7] + s0 + w[i - 16];
		//ft_membits(&w[i],0,sizeof(uint32_t));
		i++;
	}
	return (w);
}

t_hash					*sha256(void *data, size_t len_data)
{
	t_sha256	e;
	t_hash		*f_hash;

	e = (t_sha256){.h0 = SHA256_H0, .h1 = SHA256_H1, .h2 = SHA256_H2,
		.h3 = SHA256_H3, .h4 = SHA256_H4, .h5 = SHA256_H5, .h6 = SHA256_H6,
		.h7 = SHA256_H7};
	padding_sha256(&(e.p), data, len_data);
	while (e.p.offest < e.p.new_len)
	{
		e.w = set_w_sha256(e.p.str_bits, e.p.offest);
		e.a = e.h0;
		e.b = e.h1;
		e.c = e.h2;
		e.d = e.h3;
		e.e = e.h4;
		e.f = e.h5;
		e.g = e.h6;
		e.h = e.h7;
		printf("%x\n",e.a);
		calc_sha256(&e);
		e.h0 += e.a;
		e.h1 += e.b;
		e.h2 += e.c;
		e.h3 += e.d;
		e.h4 += e.e;
		e.h5 += e.f;
		e.h6 += e.g;
		e.h7 += e.h;
		e.p.offest += 64;
	}
	f_hash = set_hash2sha256(&e);
	return (f_hash);
}
