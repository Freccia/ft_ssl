/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:41:07 by lfabbro           #+#    #+#             */
/*   Updated: 2019/01/18 15:28:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"
#include "base64.h"
#include "get_next_line.h"
#include "error.h"
#include <unistd.h>

static const t_ssl_cipher	g_cipher_md5 =
{
	"md5",
	"MD5",
	sizeof(t_md5),
	ft_hash_getopt,
	md5_string,
	md5_filter,
	md5_files
};

static const t_ssl_cipher	g_cipher_sha256 =
{
	"sha256",
	"SHA256",
	sizeof(t_sha256),
	ft_hash_getopt,
	sha256_string,
	sha256_filter,
	sha256_files
};

static const t_ssl_cipher	g_cipher_base64 =
{
	"base64",
	"BASE64",
	sizeof(t_base64),
	ft_base64_getopt,
	base64_string,
	base64_filter,
	base64_files
};


static const char	*g_ft_ssl_invalid_ciph =
{
	"%s: Error: '%s' is an invalid command.\n"\
	"\nStandard commands:\n"
	"\nMessage Digest commands:\n"
	"md5\n"
	"sha256\n"
	"\nCipher commands:\n"
	"base64\n"
};

uint64_t		ft_ssl_strlen(const char *msg)
{
	uint64_t	len;

	len = -1;
	while (msg[++len])
		;
	return (len);
}

void		ft_ssl_init_ctx(t_ssl_ctx *ctx)
{
	ctx->opt = 0;
	ctx->cipher[0] = g_cipher_md5;
	ctx->cipher[1] = g_cipher_sha256;
	ctx->cipher[2] = g_cipher_base64;
}

/*
** SSLCipher Body, chooses which function tu use to digest message
** ac -> arguments length
** av -> arguments pointers
** cipher -> structure pointer to the cipher algorithm
** Set bit to zero: ~(1UL << SSL_OPT_S)
** 1UL = 00000000000000000000000000000001
*/

int				ft_ssl(int ac, char **av, t_ssl_cipher *cipher)
{
	int			ret;
	int64_t		opt;

	opt = 0;
	ret = 0;
	if (ac < 1)
		return (EXIT_FAILURE);
	//ft_ssl_getopt(ac, av, cipher, &opt);
	cipher->ci_getopt(ac, av, cipher, &opt);
	if (av[g_optind])
		ret = cipher->ci_files(ac, av, opt);
	else if (!(opt & SSL_OPT_S) )//&&
			//(g_optind == 1 || (opt & SSL_OPT_R) || (opt & SSL_OPT_Q)))
		//cipher->ci_filter((opt & SSL_OPT_Q) ? 1 : 0);
		cipher->ci_filter(opt);
	return (ret);
}

/*
 * Entry function: select cipher from command line options and call ft_ssl()
 * with selected cipher's structure as argument.
 */
int				ft_ssl_getcipher(int ac, char **av, t_ssl_ctx *ctx)
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
