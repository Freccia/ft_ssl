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
	return (EXIT_SUCCESS);
}
