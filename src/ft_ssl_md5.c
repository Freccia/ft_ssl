/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:07:39 by lfabbro           #+#    #+#             */
/*   Updated: 2018/08/26 18:39:41 by lfabbro          ###   ########.fr       */
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

static int			ft_ssl_md5_getopt(int ac, char **av, int64_t *opt)
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
	uint32_t		digest[MD5_DIGEST_SIZE];

	opt = 0;
	ft_ssl_md5_getopt(ac, av, &opt);
	if (ac != 2)
		return (EXIT_FAILURE);
	/*
	if ((msg = ft_ssl_readline(STDIN_FILENO)) == NULL)
		return (EXIT_FAILURE);
	*/
	/* TODO should print void message's digest*/
	msg = av[1];
	ft_printf("msg: '%s'\n", msg);
	if ((len = ft_ssl_strlen(msg)) > UINT_MAX)
		return (ft_exit(EXIT_FAILURE, g_md5_longerr, av[0]));
	ft_printf("len: %d %x\n", len, len*8);
	md5((uint8_t*)msg, (uint32_t)len, digest);
	ft_printf("%x%x%x%x  -\n", digest[0], digest[1], digest[2], digest[3]);
	return (EXIT_SUCCESS);
}
