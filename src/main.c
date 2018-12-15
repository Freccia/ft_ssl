/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:15:19 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/15 12:12:04 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "sha256.h"
#include "base64.h"
#include "ft_ssl.h"
#include "get_next_line.h"
#include "error.h"
#include <unistd.h>

static const t_ssl_cipher	g_cipher_md5 =
{
	"md5",
	"MD5",
	sizeof(t_md5),
	md5_string,
	md5_filter,
	md5_files
};

static const t_ssl_cipher	g_cipher_sha256 =
{
	"sha256",
	"SHA256",
	sizeof(t_sha256),
	sha256_string,
	sha256_filter,
	sha256_files
};

static const t_ssl_cipher	g_cipher_base64 =
{
	"base64",
	"BASE64",
	sizeof(t_base64),
	base64_string,
	base64_filter,
	base64_files
};

static const char	*g_ft_ssl_usage =
{
	"Usage: %s [ options ] (command) [ options ]\n"\
	"		-h : Show this help message\n"\
	"digests: md5, sha256\n"
	"ciphers: base64\n"
};

static const char	*g_ft_ssl_invalid_ciph =
{
	"%s: Error: '%s' is an invalid command.\n"\
	"\nStandard commands:\n"
	"\nMessage Digest commands:\n"
	"md5\n"
	"sha256\n"
	"\nCipher commands:\n"
};

uint64_t		ft_ssl_strlen(const char *msg)
{
	uint64_t	len;

	len = -1;
	while (msg[++len])
		;
	return (len);
}

static void		ft_ssl_init_ctx(t_ssl_ctx *ctx)
{
	ctx->opt = 0;
	ctx->cipher[0] = g_cipher_md5;
	ctx->cipher[1] = g_cipher_sha256;
	ctx->cipher[2] = g_cipher_base64;
}

static int		ft_ssl_getcipher(int ac, char **av, t_ssl_ctx *ctx)
{
	int		i;

	i = 0;
	while (i < N_CIPHERS)
	{
		if (ft_strcmp(ctx->cipher[i].name, av[g_optind]) == 0)
			return (ft_ssl(ac - g_optind, &av[g_optind], &(ctx->cipher[i])));
		++i;
	}
	return (ft_exit(EXIT_FAILURE, g_ft_ssl_invalid_ciph, av[0], av[g_optind]));
}

int				main(int ac, char **av)
{
	t_ssl_ctx	ctx;

	if (ac < 2)
		return (ft_exit(EXIT_FAILURE, g_ft_ssl_usage, av[0]));
	g_optind = 1;
	ft_ssl_init_ctx(&ctx);
	return (ft_ssl_getcipher(ac, av, &ctx));
}
