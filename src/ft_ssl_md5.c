/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:43:43 by lfabbro           #+#    #+#             */
/*   Updated: 2019/01/18 20:05:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_ssl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#include <stdio.h>

static const char	*g_md5_longerr =
{
	"md5: Error: message too long.\n"\
	"	Limit fixed to 34,35 GB (34359738360 bytes)\n"
};

int			md5_file(const char *filename, uint32_t digest[])
{
	t_md5		ctx;
	int			fd;
	int			len;
	uint8_t		buffer[1024];

	len = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("md5: %s: can't be opened\n", filename);
		return (EXIT_FAILURE);
	}
	md5_init(&ctx);
	while ((len = read(fd, buffer, sizeof(buffer))))
	{
		md5_update(&ctx, buffer, len);
	}
	md5_final(&ctx, digest);
	close(fd);
	ft_memset(&ctx, 0, sizeof(ctx));
	return (EXIT_SUCCESS);
}

void		md5_filter(int opt)
{
	t_md5		ctx;
	int64_t		len;
	uint32_t	digest[MD5_DIGEST_SIZE];
	uint8_t		buffer[1024];

	len = 0;
	memset(digest, 0, sizeof(digest));
	md5_init(&ctx);
	while ((len = read(STDIN_FILENO, buffer, sizeof(buffer))))
	{
		buffer[len] = 0;
		if (opt & SSL_OPT_P)
			ft_printf("%s", buffer);
		md5_update(&ctx, buffer, len);
	}
	md5_final(&ctx, digest);
	ft_printf("%08x%08x%08x%08x\n", digest[0], digest[1], digest[2], digest[3]);
	ft_memset(&ctx, 0, sizeof(ctx));
}

void		md5_data(const uint8_t *msg, uint32_t len, uint32_t digest[])
{
	t_md5		ctx;

	md5_init(&ctx);
	md5_update(&ctx, msg, len);
	md5_final(&ctx, digest);
	ft_memset(&ctx, 0, sizeof(ctx));
}

/*
** Call SSLCipher string digest function, print output.
*/

void		md5_string(const char *msg, int opt)
{
	int64_t		len;
	uint32_t	dig[MD5_DIGEST_SIZE];

	if ((len = ft_ssl_strlen(msg)) > UINT32_MAX)
		ft_exit(EXIT_FAILURE, g_md5_longerr);
	md5_data((uint8_t*)msg, (uint32_t)len, dig);
	if (opt & SSL_OPT_Q)
		ft_printf("%08x%08x%08x%08x\n", dig[0], dig[1], dig[2], dig[3]);
	else if (opt & SSL_OPT_R)
		ft_printf("%08x%08x%08x%08x \"%s\"\n", dig[0], dig[1], dig[2], dig[3],
				msg);
	else
		ft_printf("MD5 (\"%s\") = %08x%08x%08x%08x\n",
			msg, dig[0], dig[1], dig[2], dig[3]);
}

/*
** Loop through arguments files, call SSLCipher file digest function.
*/

int			md5_files(int ac, char **av, int opt)
{
	int			i;
	int			fail;
	uint32_t	dig[MD5_DIGEST_SIZE];

	fail = 0;
	i = g_optind;
	while (i < ac && av[i])
	{
		fail = md5_file(av[i], dig);
		if (fail == 0)
		{
			if (opt & SSL_OPT_Q)
				ft_printf("%08x%08x%08x%08x\n", dig[0], dig[1], dig[2], dig[3]);
			else if (opt & SSL_OPT_R)
				ft_printf("%08x%08x%08x%08x %s\n", dig[0], dig[1], dig[2],
						dig[3], av[i]);
			else
				ft_printf("MD5 (%s) = %08x%08x%08x%08x\n",
					av[i], dig[0], dig[1], dig[2], dig[3]);
		}
		i++;
		ft_memset(dig, 0, sizeof(dig));
	}
	return (fail);
}
