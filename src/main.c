/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:21:07 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/25 15:33:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "get_next_line.h"

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

static const char			*g_ft_ssl_invalid_cyph =
{
	"%s: Error: '%s' is an invalid command.\n"\
	"\nStandard commands:\n"
	"\nMessage Digest commands:\n"
	"md5\n"
	"\nCypher commands:\n"
};

char		*ft_ssl_readline(int fd)
{
	char	*line;

	line = NULL;
	if (get_next_line_nl(fd, &line) > 0)
		return (line);
	return (NULL);
}

uint64_t	ft_ssl_strlen(char *msg)
{
	uint64_t	len;

	len = 0;
	while (msg[len++])
		;
	return (len);
}

/* TODO should implement sha1 and sha256*/
void		ft_ssl_init_ctx(t_ssl_ctx *ctx)
{
	ctx->opt = 0;
	ctx->cypher[0] = cy_md5;
//	ctx->cypher[1] = cy_sha1;
//	ctx->cypher[2] = cy_sha256;
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
	return (ft_exit(EXIT_FAILURE, g_ft_ssl_invalid_cyph, av[0], av[g_optind]));
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
