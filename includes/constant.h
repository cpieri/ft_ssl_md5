/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:15:35 by cpieri            #+#    #+#             */
/*   Updated: 2019/04/11 16:34:37 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CONSTANT_H
# define CONSTANT_H

static const t_parse	g_all_cmd[] =
{
	{"md5", "MD5", e_hash, md5, hash_opts, printing_hash, NULL},
	{"sha256", "SHA256", e_hash, sha256, hash_opts, printing_hash, NULL},
	{NULL, NULL, 0, NULL, NULL, NULL, NULL},
};

static const char *		g_hash_cmd[] =
{
	"md5",
	"sha256",
	NULL
};

static const char *		g_cipher_cmd[] =
{
	"base64",
	"des",
	"des-ecb",
	"des-cbc",
	NULL
};

#endif