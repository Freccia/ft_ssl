/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_getopt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 22:41:12 by marvin            #+#    #+#             */
/*   Updated: 2019/04/04 11:54:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

static const char	*g_des_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\
	"		-a : decode/encode the input/output in base64\n"\
	"		-d : decryption mode\n"\
	"		-e : encryption mode (default)\n"\
	"		-i : input file for message\n"\
	"		-k : key in hex is the next arguement\n"\
	"		-o : output file for message\n"\
	"		-p : password in ascii is the next argument\n"\
	"		-s : the salt in hex is the next argument\n"\
	"		-v : initialization vector in hex is the next argument\n"\
	"\n"\
};

char *ft_des_getopt(int ac, char **av, t_ssl_cipher *ci, int64_t *opt)
{
	int		o;
	t_des	*ctx;

	(void)ci;
	g_optind = 1;
	g_optreset = 1;

	if ((ctx = (t_des *)malloc(sizeof(*ctx))) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
	ft_memset(ctx, 0, sizeof(*ctx));

	while (g_optind < ac && (o = ft_getopt(ac, av, DES_OPTIONS)) != -1)
	{
//		ft_printf("optind: %d\n", g_optind);
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_des_usage, av[0]);
		else if (o == 'a')
			*opt |= SSL_OPT_B64;
		else if (o == 'd')
			*opt = (*opt ^ SSL_OPT_ENC) | SSL_OPT_DEC;
		else if (o == 'e')
			*opt |= SSL_OPT_ENC;
		else if (o == 'i')
			ctx->infile = g_optarg;
		else if (o == 'k')
			ctx->key = g_optarg;
		else if (o == 'o')
			ctx->outfile = g_optarg;
		else if (o == 'p')
			ctx->passwd = g_optarg;
		else if (o == 's' && (*opt |= SSL_OPT_S))
			ctx->salt = g_optarg;
		else if (o =='v')
			ctx->ivect = g_optarg;
	}
	ft_des(ctx, *opt);
	free(ctx);
	return (av[ac]);
}
