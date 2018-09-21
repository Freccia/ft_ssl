/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:02:58 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/21 10:50:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <limits.h>

#include <stdio.h>

static const char	*g_ssl_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\
	"		-p : echo STDIN to STDOUT and append the checksum to STDOUT\n"\
	"		-q : quiet mode\n"\
	"		-r : reverse the format of the output\n"\
	"		-s : print the sum of the given string\n"
};

static const char	*g_ssl_longerr =
{
	"%s: Error: message too long.\n"\
	"	Limit fixed to 34,35 GB (34359738360 bytes)\n"
};

/*
** Call SSLCypher string digest function, print output.
*/
static void	ft_ssl_string(const t_ssl_cypher *cypher, char *msg, int opt)
{
	int64_t		len;
	uint32_t	dig[cypher->digest_size];

	/* Check overflow */
	if ((len = ft_ssl_strlen(msg)) > UINT32_MAX)
		ft_exit(EXIT_FAILURE, g_ssl_longerr, cypher->name);
	cypher->cy_data((uint8_t*)msg, (uint32_t)len, dig);
	if (opt & SSL_OPT_Q)
		ft_printf("%x%x%x%x\n", dig[0], dig[1], dig[2], dig[3]);
	else if (opt & SSL_OPT_R)
		ft_printf("%x%x%x%x \"%s\"\n", dig[0], dig[1], dig[2], dig[3], msg);
	else
		ft_printf("%s (\"%s\") = %x%x%x%x\n",
			cypher->cy_name, msg, dig[0], dig[1], dig[2], dig[3]);
}

/*
** Loop through arguments files, call SSLCypher file digest function.
*/
static int	ft_ssl_files(int ac, char **av, t_ssl_cypher *cypher, int opt)
{
	int			i;
	int			fail;
	uint32_t	dig[cypher->digest_size];

	fail = 0;
	i = g_optind;
	while (i < ac && av[i])
	{
		fail = cypher->cy_file(av[i], dig);
		if (opt & SSL_OPT_Q)
			ft_printf("%x%x%x%x\n", dig[0], dig[1], dig[2], dig[3]);
		else if (opt & SSL_OPT_R)
			ft_printf("%x%x%x%x %s\n", dig[0], dig[1], dig[2], dig[3], av[i]);
		else
			ft_printf("%s (%s) = %x%x%x%x\n",
				cypher->cy_name, av[1], dig[0], dig[1], dig[2], dig[3]);
		i++;
	}
	return (fail);
}

/*
** Get options for SSLCypher, call SSLCypher digest functions.
** (optind starts at zero to match the current option/argument)
*/
static char	*ft_ssl_getopt(int ac, char **av, t_ssl_cypher *cypher,
	int64_t *opt)
{
	int		o;

	g_optind = 1;
	g_optreset = 1;
	//ft_printf("ac: %d -- av: %s\n", ac, av[0]);
	while (g_optind < ac && (o = ft_getopt(ac, av, SSL_OPTIONS)) != -1)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_ssl_usage, av[0]);
		if (o == 's' && (*opt |= SSL_OPT_S))
			ft_ssl_string(cypher, g_optarg, *opt);
		else if (o == 'p')
			cypher->cy_filter((*opt & SSL_OPT_Q) ? 1 : 0);
		else if (o == 'q')
			*opt |= SSL_OPT_Q;
		else if (o == 'r')
			*opt |= SSL_OPT_R;
	}
	return (av[ac]);
}

/*
** SSLCypher Body, chooses which function tu use to digest message
** ac -> arguments lenght
** av -> arguments pointers
** cypher -> structure pointer to the cypher algorithm
** Set bit to zero: ~(1UL << SSL_OPT_S)
** 1UL = 00000000000000000000000000000001
*/
int			ft_ssl(int ac, char **av, t_ssl_cypher *cypher)
{
	int			ret;
	int64_t		opt;

	opt = 0;
	ret = 0;
	if (ac < 1)
		return (EXIT_FAILURE);
	ft_ssl_getopt(ac, av, cypher, &opt);
	if (av[g_optind])
		ret = ft_ssl_files(ac, av, cypher, opt);
	else if (!(opt & SSL_OPT_S) &&
			(g_optind == 1 || (opt & SSL_OPT_R) || (opt & SSL_OPT_Q)))
		cypher->cy_filter((opt & SSL_OPT_Q) ? 1 : 0);
	return (ret);
}
