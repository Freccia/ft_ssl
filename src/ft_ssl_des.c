/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:58:25 by marvin            #+#    #+#             */
/*   Updated: 2019/04/04 11:53:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "des.h"

#include <sys/stat.h>

int		ft_des(t_des *ctx, const int opt)
{
	(void)ctx;
	(void)opt;
	ft_printf("DES Structure: \n");
	ft_printf("    ctx->buff: %s\n", ctx->buff);
	ft_printf("    ctx->infile: %s\n", ctx->infile);
	ft_printf("    ctx->outfile: %s\n", ctx->outfile);
	ft_printf("    ctx->key: %s\n", ctx->key);
	ft_printf("    ctx->passwd: %s\n", ctx->passwd);
	ft_printf("    ctx->salt: %s\n", ctx->salt);
	ft_printf("    ctx->ivect: %s\n", ctx->ivect);
	ft_printf("\n");

	uint64_t	key;
	uint64_t	ivect;
	uint64_t	salt;
	int			fdin;
	int			fdout;
	struct stat	infstat;
	uint64_t	inlen;
	int 		i;

	i = 0;
	if (ft_ishex(ctx->key) == EXIT_FAILURE)
		ft_exit(EXIT_FAILURE, "Wrong key.\n");
	if (ft_ishex(ctx->salt) == EXIT_FAILURE)
		ft_exit(EXIT_FAILURE, "Wrong salt.\n");
	if (ft_ishex(ctx->ivect) == EXIT_FAILURE)
		ft_exit(EXIT_FAILURE, "Wrong ivect.\n");

	key = ft_atoul_hex(ctx->key);
	ivect = ft_atoul_hex(ctx->ivect);
	salt = ft_atoul_hex(ctx->salt);

	if ((fdin = open(ctx->infile, O_RDONLY)) < 0)
		ft_exit(EXIT_FAILURE, "Failed to open file %s\n", ctx->infile);
	if ((fdout = open(ctx->outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		ft_exit(EXIT_FAILURE, "Failed to open file %s\n", ctx->outfile);
	if (fstat(int fdin, struct stat *infstat) < 0)
		ft_exit(EXIT_FAILURE, "Failed fstat on file: %s\n", ctx->infile);

	// PBKDF: SHA256

	inlen = (uint64_t) infstat.st_size;
	while (i < inlen)
	{
		// encrypt block

		i =+ 64;
	}
	if (close(fdin) < 0)
		ft_exit(EXIT_FAILURE, "Failed closing file: %s\n", ctx->infile);
	if (close(fdout) < 0)
		ft_exit(EXIT_FAILURE, "Failed closing file: %s\n", ctx->outfile);
	return (EXIT_SUCCESS);
}
