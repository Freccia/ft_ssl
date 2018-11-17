/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:27:37 by lfabbro           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static unsigned char g_padding[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void		md5_transform(uint32_t regs[4], const uint8_t block[64])
{
	uint32_t	regz[4];
	uint32_t	x[16];

	regz[MD5_A] = regs[MD5_A];
	regz[MD5_B] = regs[MD5_B];
	regz[MD5_C] = regs[MD5_C];
	regz[MD5_D] = regs[MD5_D];
	decode(x, block, 64);
	md5_transform_round_one(&regz[0], x);
	md5_transform_round_two(&regz[0], x);
	md5_transform_round_three(&regz[0], x);
	md5_transform_round_four(&regz[0], x);
	regs[MD5_A] += regz[MD5_A];
	regs[MD5_B] += regz[MD5_B];
	regs[MD5_C] += regz[MD5_C];
	regs[MD5_D] += regz[MD5_D];
	ft_memset(&x, 0, sizeof(x));
}

void			md5_init(t_md5 *ctx)
{
	ctx->bitcount[0] = 0;
	ctx->bitcount[1] = 0;
	ctx->regs[MD5_A] = 0x67452301;
	ctx->regs[MD5_B] = 0xefcdab89;
	ctx->regs[MD5_C] = 0x98badcfe;
	ctx->regs[MD5_D] = 0x10325476;
	ft_memset(ctx->buff, 0, MD5_BUFFER_SIZE);
}

void			md5_update(t_md5 *ctx, const uint8_t *data, uint32_t datalen)
{
	uint32_t	i;
	uint32_t	idx;
	uint32_t	partlen;

	idx = (uint32_t)((ctx->bitcount[0] >> 3) & 0x3F);
	if ((ctx->bitcount[0] += (uint32_t)datalen << 3) < ((uint32_t)datalen << 3))
		ctx->bitcount[1]++;
	ctx->bitcount[1] += ((uint32_t)datalen >> 29);
	partlen = 64 - idx;
	if (datalen >= partlen)
	{
		ft_memcpy((void*)&ctx->buff[idx], (const void*)data, partlen);
		md5_transform(ctx->regs, ctx->buff);
		i = partlen;
		while (i + 63 < datalen)
		{
			md5_transform(ctx->regs, &data[i]);
			i += 64;
		}
		idx = 0;
	}
	else
		i = 0;
	ft_memcpy((void*)&ctx->buff[idx], (const void*)&data[i], datalen - i);
}

static void		md5_pad(t_md5 *ctx)
{
	uint8_t		bits[8];
	uint32_t	idx;
	uint32_t	padlen;

	ft_memset(bits, 0, 8);
	encode(bits, ctx->bitcount, 8);
	idx = (uint32_t)((ctx->bitcount[0] >> 3) & 0x3F);
	padlen = (idx < 56) ? (56 - idx) : (120 - idx);
	md5_update(ctx, g_padding, padlen);
	md5_update(ctx, bits, 8);
}

/*
**	MD5_BUFFER_SIZE: 64 bytes == 512 bits
**	0x3f == 63 == 0b111111
*/

void			md5_final(t_md5 *ctx, uint32_t digest[MD5_DIGEST_SIZE])
{
	uint8_t		*p;

	md5_pad(ctx);
	encode((uint8_t*)digest, ctx->regs, 4);
	p = (uint8_t*)digest;
	p[0] = (ctx->regs[MD5_A] & 0xff000000) >> 24;
	p[1] = (ctx->regs[MD5_A] & 0x00ff0000) >> 16;
	p[2] = (ctx->regs[MD5_A] & 0x0000ff00) >> 8;
	p[3] = (ctx->regs[MD5_A] & 0x000000ff);
	p[4] = (ctx->regs[MD5_B] & 0xff000000) >> 24;
	p[5] = (ctx->regs[MD5_B] & 0x00ff0000) >> 16;
	p[6] = (ctx->regs[MD5_B] & 0x0000ff00) >> 8;
	p[7] = (ctx->regs[MD5_B] & 0x000000ff);
	p[8] = (ctx->regs[MD5_C] & 0xff000000) >> 24;
	p[9] = (ctx->regs[MD5_C] & 0x00ff0000) >> 16;
	p[10] = (ctx->regs[MD5_C] & 0x0000ff00) >> 8;
	p[11] = (ctx->regs[MD5_C] & 0x000000ff);
	p[12] = (ctx->regs[MD5_D] & 0xff000000) >> 24;
	p[13] = (ctx->regs[MD5_D] & 0x00ff0000) >> 16;
	p[14] = (ctx->regs[MD5_D] & 0x0000ff00) >> 8;
	p[15] = (ctx->regs[MD5_D] & 0x000000ff);
	ft_bzero(ctx, sizeof(*ctx));
}
