/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:08:47 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/13 20:14:18 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "ft_ssl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static const char	*g_sha256_longerr =
{
	"sha256: Error: message too long.\n"\
	"	Limit fixed to 34,35 GB (34359738360 bytes)\n"
};

void		sha256_data(const uint8_t *msg, uint32_t len, uint32_t digest[])
{
	t_sha256	ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, msg, len);
	sha256_final(&ctx, digest);
	ft_memset(&ctx, 0, sizeof(ctx));
}

void		sha256_filter(int quiet)
{
	t_sha256	ctx;
	int64_t		len;
	uint32_t	digest[SHA256_DIGEST_SIZE];
	uint8_t		buffer[1024];

	len = 0;
	sha256_init(&ctx);
	while ((len = read(STDIN_FILENO, buffer, sizeof(buffer))))
	{
		buffer[len] = 0;
		if (!quiet)
			ft_printf("%s", buffer);
		sha256_update(&ctx, buffer, len);
	}
	sha256_final(&ctx, digest);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", digest[0], digest[1],
			digest[2], digest[3], digest[4], digest[5], digest[6], digest[7]);
	ft_memset(&ctx, 0, sizeof(ctx));
}

/*
** Call SSLCipher string digest function, print output.
*/

void		sha256_string(const char *msg, int opt)
{
	int64_t		len;
	uint32_t	dig[SHA256_DIGEST_SIZE];

	if ((len = ft_ssl_strlen(msg)) > UINT32_MAX)
		ft_exit(EXIT_FAILURE, g_sha256_longerr);
	sha256_data((uint8_t*)msg, (uint32_t)len, dig);
	if (opt & SSL_OPT_Q)
		ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", dig[0], dig[1], dig[2],
				dig[3], dig[4], dig[5], dig[6], dig[7]);
	else if (opt & SSL_OPT_R)
		ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x \"%s\"\n", dig[0], dig[1],
				dig[2], dig[3], dig[4], dig[5], dig[6], dig[7], msg);
	else
		ft_printf("sha256 (\"%s\") = %08x%08x%08x%08x%08x%08x%08x%08x\n", msg,
				dig[0], dig[1], dig[2], dig[3], dig[4], dig[5], dig[6], dig[7]);
}

int			sha256_file(const char *filename, uint32_t digest[])
{
	t_sha256	ctx;
	int			fd;
	int			len;
	uint8_t		buffer[1024];

	len = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%s can't be opened\n", filename);
		return (EXIT_FAILURE);
	}
	sha256_init(&ctx);
	while ((len = read(fd, buffer, sizeof(buffer))))
	{
		buffer[len] = 0;
		sha256_update(&ctx, buffer, len);
	}
	sha256_final(&ctx, digest);
	close(fd);
	ft_memset(&ctx, 0, sizeof(ctx));
	return (EXIT_SUCCESS);
}

/*
** Loop through arguments files, call SSLCipher file digest function.
*/

int			sha256_files(int ac, char **av, int opt)
{
	int			i;
	int			fail;
	uint32_t	dig[SHA256_DIGEST_SIZE];

	fail = 0;
	i = g_optind;
	while (i < ac && av[i])
	{
		fail = sha256_file(av[i], dig);
		if (fail == 0)
		{
			if (opt & SSL_OPT_Q)
				ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", dig[0], dig[1],
					dig[2], dig[3], dig[4], dig[5], dig[6], dig[7]);
			else if (opt & SSL_OPT_R)
				ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x %s\n", dig[0],
				dig[1], dig[2], dig[3], dig[4], dig[5], dig[6], dig[7], av[i]);
			else
				ft_printf("sha256 (%s) = %08x%08x%08x%08x%08x%08x%08x%08x\n",
					av[1], dig[0], dig[1], dig[2], dig[3], dig[4], dig[5],
						dig[6], dig[7]);
		}
		i++;
		ft_memset(&dig, 0, sizeof(dig));
	}
	return (fail);
}
