/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:07:39 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/25 17:37:28 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"
#include <limits.h>

static const char	*g_md5_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\
	"		-p : echo STDIN to STDOUT and append the checksum to STDOUT\n"\
	"		-q : quiet mode\n"\
	"		-r : reverse the format of the output\n"\
	"		-s : print the sum of the given string\n"
};

static const char	*g_md5_longerr =
{
	"%s: Error: message too long.\n"\
	"	Limit fixed to 34,35 GB (34359738360 bytes)\n"
};

int			ft_ssl_md5_getopt(int ac, char **av, int64_t *opt)
{
	int		o;

	g_optind = 1;
	g_optreset = 1;
	while (g_optind < ac && (o = ft_getopt(ac, av, MD5_OPTIONS)) != -1)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_md5_usage, av[0]);
		*opt |= (o == 'p') ? MD5_OPT_P : 0;
		*opt |= (o == 'q') ? MD5_OPT_Q : 0;
		*opt |= (o == 'r') ? MD5_OPT_R : 0;
		*opt |= (o == 's') ? MD5_OPT_S : 0;
	}
	return (EXIT_SUCCESS);
}

int			ft_ssl_md5(int ac, char **av)
{
	int64_t			opt;
	int64_t			len;
	char			*msg;
	unsigned char	digest[16];

	opt = 0;
	ft_ssl_md5_getopt(ac, av, &opt);
	if ((msg = ft_ssl_readline(STDIN_FILENO)) != NULL)
		return (EXIT_SUCCESS);
	if ((len = ft_ssl_strlen(msg)) > UINT_MAX)
		return (ft_exit(EXIT_FAILURE, g_md5_longerr, av[0]));
	md5((unsigned char*)msg, (t_int_md5)len, digest);
	return (EXIT_SUCCESS);
}
