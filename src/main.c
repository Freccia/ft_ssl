/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:21:07 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/20 19:48:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char	*g_ft_ssl_usage =
{
	"Usage: %s [ options ] cypher [ options ]\n"\
	"		-h : Show this help message\n"\
	"cypher: md5, sha1, sha256\n"
};

int			ft_ssl_getcypher(char *str)
{
	if (ft_strlen(str) == 0)
		return (EXIT_FAILURE);
	if (ft_strcmp(str, "md5") == EXIT_SUCCESS)
		return (SSL_CYPH_MD5);
	if (ft_strcmp(str, "sha1") == EXIT_SUCCESS)
		return (SSL_CYPH_SHA1);
	if (ft_strcmp(str, "sha256") == EXIT_SUCCESS)
		return (SSL_CYPH_SHA256);
	return (EXIT_FAILURE);
}

/*
int		o;
while ((o = ft_getopt(ac, av, SSL_OPTIONS)) != EXIT_FAILURE)
{
	if (o == 'h' || o == BADCH || o == BADARG)
		ft_exit(EXIT_FAILURE, g_usage, av[0]);
	ctx->opt += (o == 'p') ? SSL_OPT_P : 0;
}
*/

int			ft_ssl_getopt(int ac, char **av, t_ssl_ctx *ctx)
{
	(void)ac;
	g_optind = 1;
	if ((ctx->cypher = ft_ssl_getcypher(av[g_optind++])) == EXIT_FAILURE)
		ft_exit(EXIT_FAILURE, g_ft_ssl_usage, av[0]);
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	t_ssl_ctx	ctx;

	if (ac <= 1)
		return ft_exit(EXIT_FAILURE, g_ft_ssl_usage, av[0]);
	ft_ssl_getopt(ac, av, &ctx);
	if (ctx.cypher == SSL_CYPH_MD5)
		return (ft_ssl_md5(ac - g_optind, &av[g_optind]));
	/* TODO should implement sha1 and sha256*/
	return (EXIT_SUCCESS);
}
