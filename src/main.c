/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:15:19 by lfabbro           #+#    #+#             */
/*   Updated: 2019/01/18 15:07:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "error.h"

static const char	*g_ft_ssl_usage =
{
	"Usage: %s [ options ] (command) [ options ]\n"\
	"		-h : Show this help message\n"\
	"digests: md5, sha256\n"
	"ciphers: base64\n"
};

int				main(int ac, char **av)
{
	t_ssl_ctx	ctx;

	if (ac < 2)
		return (ft_exit(EXIT_FAILURE, g_ft_ssl_usage, av[0]));
	g_optind = 1;
	ft_ssl_init_ctx(&ctx);
	return (ft_ssl_getcipher(ac, av, &ctx));
}
