/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:21:07 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/25 11:28:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
int			ft_ssl_getopt(int ac, char **av, t_ssl_ctx *ctx)
{
	(void)ac;
	int		o;
	while ((o = ft_getopt(ac, av, SSL_OPTIONS)) != EXIT_FAILURE)
	{
		if (o == 'h' || o == BADCH || o == BADARG)
			ft_exit(EXIT_FAILURE, g_usage, av[0]);
		ctx->opt += (o == 'p') ? SSL_OPT_P : 0;
	}
	return (EXIT_SUCCESS);
}
*/

static const t_ssl_cypher	cy_md5 =
{
	"md5",
	ft_ssl_md5
};

static const char			*g_ft_ssl_usage =
{
	"Usage: %s [ options ] cypher [ options ]\n"\
	"		-h : Show this help message\n"\
	"cypher: md5, sha1, sha256\n"
};

static const char			*g_ft_ssl_invalid_cypher =
{
	"%s: Error: '%s' is an invalid command.\n"\
	"\nStandard commands:\n"
	"\nMessage Digest commands:\n"
	"md5\n"
	"\nCypher commands:\n"
};

void		ft_ssl_init_ctx(t_ssl_ctx *ctx)
{
	ctx->opt = 0;
	ctx->cypher[0] = cy_md5;
/* TODO should implement sha1 and sha256*/
//	ctx->cypher[1] = {"sha1", ft_ssl_sha1};
//	ctx->cypher[2] = {"sha256", ft_ssl_sha256};
}

int			ft_ssl_getcypher(int ac, char **av, t_ssl_ctx *ctx)
{
	int		i;

	i = 0;
	while (i < N_CYPHERS)
	{
		if (ft_strcmp(ctx->cypher[i].name, av[g_optind]) == 0)
			return (ctx->cypher[i].ft_cypher(ac - g_optind, &av[g_optind]));
		++i;
	}
	ft_exit(EXIT_FAILURE, g_ft_ssl_invalid_cypher, av[0], av[1]);
	return (EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_ssl_ctx	ctx;

	if (ac < 2)
		return ft_exit(EXIT_FAILURE, g_ft_ssl_usage, av[0]);
	g_optind = 1;
	ft_ssl_init_ctx(&ctx);
	ft_ssl_getcypher(ac, av, &ctx);
	return (EXIT_SUCCESS);
}
