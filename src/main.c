/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:21:07 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/08 17:37:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_ssl.h"
#include "get_next_line.h"
#include "error.h"
#include <unistd.h>

static const t_ssl_cypher	cypher_md5 =
{
	"md5",
	"MD5",
	MD5_DIGEST_SIZE,
	md5_file,
	md5
};

static const char			*g_ft_ssl_usage =
{
	"Usage: %s [ options ] (cypher) [ options ]\n"\
	"		-h : Show this help message\n"\
	"cypher: md5, sha256\n"
};

static const char			*g_ft_ssl_invalid_cyph =
{
	"%s: Error: '%s' is an invalid command.\n"\
	"\nStandard commands:\n"
	"\nMessage Digest commands:\n"
	"md5\n"
	"sha256\n"
	"\nCypher commands:\n"
};

char		*ft_ssl_readin(int fd)
{
	char		buf[64];
	char		*line;
	char		*tmp;
	int32_t		ret;

	tmp = NULL;
	line = NULL;
	while ((ret = read(fd, &buf, 64)))
	{
		buf[ret] = 0;
		tmp = line;
		if ((line = ft_strjoin(line, buf)) == NULL)
			ft_exit(EXIT_FAILURE, FAIL_MALLOC);
		free(tmp);
	}
	return (line);
}

uint64_t	ft_ssl_strlen(char *msg)
{
	uint64_t	len;

	len = -1;
	while (msg[++len])
		;
	return (len);
}

/* TODO should implement sha256*/
static void		ft_ssl_init_ctx(t_ssl_ctx *ctx)
{
	ctx->opt = 0;
	ctx->cypher[0] = cypher_md5;
//	ctx->cypher[2] = cy_sha256;
//	ctx->cypher[1] = cy_sha1;
}

static int			ft_ssl_getcypher(int ac, char **av, t_ssl_ctx *ctx)
{
	int		i;

	i = 0;
	while (i < N_CYPHERS)
	{
		if (ft_strcmp(ctx->cypher[i].name, av[g_optind]) == 0)
			return (ft_ssl(ac - g_optind, &av[g_optind], &(ctx->cypher[i])));
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
