/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 19:07:39 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/20 19:48:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static const char	*g_md5_usage =
{
	"Usage: %s [ options ]\n"\
	"		-h : Show this help message\n"\
	"		-p : echo STDIN to STDOUT and append the checksum to STDOUT\n"\
	"		-q : quiet mode\n"\
	"		-r : reverse the format of the output\n"\
	"		-s : print the sum of the given string\n"\
};

int			ft_ssl_md5_getopt(int ac, char **av, int64_t *opt)
{
	int		o;

	g_optind = 0;
	while (/*TODO removeme*/ac > 0 && (o = ft_getopt(ac, av, MD5_OPTIONS)) != EXIT_FAILURE)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_md5_usage, av[0]);
		*opt += (o == 'p') ? MD5_OPT_P : 0;
		*opt += (o == 'q') ? MD5_OPT_Q : 0;
		*opt += (o == 'r') ? MD5_OPT_R : 0;
		*opt += (o == 's') ? MD5_OPT_S : 0;
	}
	return (EXIT_SUCCESS);
}

int			ft_ssl_md5(int ac, char **av)
{
	(void)ac;
	(void)av;
	int64_t		opt;

	opt = 0;
	ft_ssl_md5_getopt(ac, av, &opt);
	return (EXIT_SUCCESS);
}
