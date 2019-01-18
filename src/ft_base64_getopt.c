/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64_getopt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:13:46 by marvin            #+#    #+#             */
/*   Updated: 2019/01/18 16:35:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <limits.h>

static const char	*g_base64_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\
	"		-p : echo STDIN to STDOUT and append the checksum to STDOUT\n"\
	"		-q : quiet mode\n"\
	"		-r : reverse the format of the output\n"\
	"		-s : print the sum of the given string\n"
	"		-e : encode mode\n"
	"		-d : dencode mode\n"
};

/*
** Get options for SSLCipher, call SSLCipher digest functions.
** (optind starts at zero to match the current option/argument)
*/

char		*ft_base64_getopt(int ac, char **av, t_ssl_cipher *cipher,
		int64_t *opt)
{
	int		o;

	g_optind = 1;
	g_optreset = 1;
	while (g_optind < ac && (o = ft_getopt(ac, av, SSL_OPTIONS)) != -1)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_base64_usage, av[0]);
		if (o == 's' && (*opt |= SSL_OPT_S))
			cipher->ci_string(g_optarg, *opt);
		else if (o == 'p')
			cipher->ci_filter((*opt & SSL_OPT_Q) ? 1 : 0);
		else if (o == 'q')
			*opt |= SSL_OPT_Q;
		else if (o == 'r')
			*opt |= SSL_OPT_R;
		else if (o == 'e')
			*opt |= SSL_OPT_ENC;
		else if (o == 'd')
			*opt |= SSL_OPT_DEC;
	}
	return (av[ac]);
}
