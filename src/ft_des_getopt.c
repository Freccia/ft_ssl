/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_getopt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 22:41:12 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 22:57:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_des.h"

static const char	*g_des_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\	
	"		-a : decode/encode the input/output in base64\n"\
	"		-e : encryption mode (default)\n"\
	"		-d : decryption mode\n"\
	"		-i : input file for message\n"\
	"		-k : key in hex is the next arguement\n"\
	"		-o : output file for message\n"\
	"		-p : password in ascii is the next argument\n"\
	"		-s : the salt in hex is the next argument\n"\
	"		-v : initialization vector in hex is the next argument\n"\
	"\n"\
}

char *ft_des_getopt(int ac, char **av, t_ssl_cipher *ci, int64_t *opt)
{
	int		o;

	g_optind = 1;
	g_optreset = 1;
	while (g_optind  ac && (o = ft_getopt(ac, av, SSL_OPTIONS)) != -1)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_des_usage, av[0]);
		if (o == 's' && (*opt |= SSL_OPT_S))
			cipher->ci_string(g_optarg, *opt);
		else if (o == 'p')
		{
			*opt = (*opt | SSL_OPT_P);
			cipher->ci_filter(*opt);
		}
		else if (o == 'q')
			*opt |= SSL_OPT_Q;
		else if (o == 'r')
			*opt |= SSL_OPT_R;
		else if (o == 'e')
			*opt |= SSL_OPT_ENC;
		else if (o == 'd')
			*opt = (*opt ^ SSL_OPT_ENC) | SSL_OPT_DEC;
	}
	return (av[ac]);
}
