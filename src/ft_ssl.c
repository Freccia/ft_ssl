/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:41:07 by lfabbro           #+#    #+#             */
/*   Updated: 2018/11/17 15:50:18 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <limits.h>

static const char	*g_ssl_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\
	"		-p : echo STDIN to STDOUT and append the checksum to STDOUT\n"\
	"		-q : quiet mode\n"\
	"		-r : reverse the format of the output\n"\
	"		-s : print the sum of the given string\n"
};

/*
** Get options for SSLCipher, call SSLCipher digest functions.
** (optind starts at zero to match the current option/argument)
*/

static char		*ft_ssl_getopt(int ac, char **av, t_ssl_cipher *cipher,
	int64_t *opt)
{
	int		o;

	g_optind = 1;
	g_optreset = 1;
	while (g_optind < ac && (o = ft_getopt(ac, av, SSL_OPTIONS)) != -1)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_ssl_usage, av[0]);
		if (o == 's' && (*opt |= SSL_OPT_S))
			cipher->ci_string(g_optarg, *opt);
		else if (o == 'p')
			cipher->ci_filter((*opt & SSL_OPT_Q) ? 1 : 0);
		else if (o == 'q')
			*opt |= SSL_OPT_Q;
		else if (o == 'r')
			*opt |= SSL_OPT_R;
	}
	return (av[ac]);
}

/*
** SSLCipher Body, chooses which function tu use to digest message
** ac -> arguments lenght
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
	ft_ssl_getopt(ac, av, cipher, &opt);
	if (av[g_optind])
		ret = cipher->ci_files(ac, av, opt);
	else if (!(opt & SSL_OPT_S) &&
			(g_optind == 1 || (opt & SSL_OPT_R) || (opt & SSL_OPT_Q)))
		cipher->ci_filter((opt & SSL_OPT_Q) ? 1 : 0);
	return (ret);
}
