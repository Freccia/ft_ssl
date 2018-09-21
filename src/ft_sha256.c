/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:43:01 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/21 11:42:50 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

const uint32_t k = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
}

void		sha256_transform(t_sha56 *ctx, const uint8_t data[])
{
	t_transform_ctx t;
	uint32_t i;
	uint32_t j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		 t->m[i] = (data[j] << 24) | (data[j + 1] << 16) |
						(data[j + 2] << 8) | (data[j + 3]);
		++i;
		j += 4;
	}
	while (i < 64)
	{
		t->m[i] = SSIG1(t->m[i - 2]) + t->m[i - 7]
					+ SSIG0(t->m[i - 15]) + t->m[i - 16];
		++i;
	}
	t->a = ctx->regs[0];
	t->b = ctx->regs[1];
	t->c = ctx->regs[2];
	t->d = ctx->regs[3];
	t->e = ctx->regs[4];
	t->f = ctx->regs[5];
	t->g = ctx->regs[6];
	t->h = ctx->regs[7];
	i = 0;
	while (i < 64)
	{
		t->t1 = t->h + EP1(t->e) + CH(t->e, t->f, t->g) + t->k[i] + t->m[i];
		t->t2 = EP0(t->a) + MAJ(t->a, t->b, t->c);
		t->h = t->g;
		t->g = t->f;
		t->f = t->e;
		t->e = t->d + t->t1;
		t->d = t->c;
		t->c = t->b;
		t->b = t->a;
		t->a = t->t1 + t->t2;
	}
	ctx->regs[0] += t->a;
	ctx->regs[1] += t->b;
	ctx->regs[2] += t->c;
	ctx->regs[3] += t->d;
	ctx->regs[4] += t->e;
	ctx->regs[5] += t->f;
	ctx->regs[6] += t->g;
	ctx->regs[7] += t->h;

}

void		sha256_init(t_sha256 *ctx)
{
	ctx->bitlen = 0;
	ctx->datalen = 0;
	ctx->regs[0] = 0x6a09e667;
	ctx->regs[1] = 0xbb67ae85;
	ctx->regs[2] = 0x3c6ef372;
	ctx->regs[3] = 0xa54ff53a;
	ctx->regs[4] = 0x510e527f;
	ctx->regs[5] = 0x9b05688c;
	ctx->regs[6] = 0x1f83d9ab;
	ctx->regs[7] = 0x5be0cd19;
}


