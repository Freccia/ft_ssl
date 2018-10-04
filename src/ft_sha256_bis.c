/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:18:27 by lfabbro           #+#    #+#             */
/*   Updated: 2018/10/04 17:11:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void		sha256_transform_bis(t_sha256 *ctx, const uint8_t data[],
		t_transform_ctx *t)
{
	t->i = 0;
	t->j = 0;
	while (t->i < 16)
	{
		t->m[t->i] = (data[t->j] << 24) | (data[t->j + 1] << 16) |
						(data[t->j + 2] << 8) | (data[t->j + 3]);
		++t->i;
		t->j += 4;
	}
	while (t->i < 64)
	{
		t->m[t->i] = SSIG1(t->m[t->i - 2]) + t->m[t->i - 7]
					+ SSIG0(t->m[t->i - 15]) + t->m[t->i - 16];
		++t->i;
	}
	t->a = ctx->regs[0];
	t->b = ctx->regs[1];
	t->c = ctx->regs[2];
	t->d = ctx->regs[3];
	t->e = ctx->regs[4];
	t->f = ctx->regs[5];
	t->g = ctx->regs[6];
	t->h = ctx->regs[7];
	t->i = 0;
	t->j = 0;
}
