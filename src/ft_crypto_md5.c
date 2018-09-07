/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crypto_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:27:37 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/07 18:19:57 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

/*
** uint8_t		*md5(uint8_t *msg, uint32_t len, uint8_t *dig);
** void				md5_init(t_md5 *ctx);
** void				md5_update(t_md5 *ctx);
** void				m5_final(uint8_t *dig, t_md5 *ctx);
*/

/*
** Decodes input (unsigned char) into output (uint32_t). Assumes len is
** a multiple of 4.
*/
static void Decode( uint32_t *output, uint8_t *input, uint32_t len )
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
			(((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
}

/*
static void			md5_debug(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	uint8_t *p;
	p = (uint8_t *)&a;
	ft_printf("\nabcd: %x %x %x %x\n", a, b, c, d);
	ft_printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&b;
	ft_printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&c;
	ft_printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&d;
	ft_printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
}
*/

static void			md5_transform(t_md5 *ctx, uint8_t *ptr)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	x[16];

	a = ctx->regs[MD5_A];
	b = ctx->regs[MD5_B];
	c = ctx->regs[MD5_C];
	d = ctx->regs[MD5_D];

	Decode(x, ptr, 64);

	/* Round 1 */
#ifdef DEBUG
	int i = 0;
	md5_debug(a, b, c, d);
	ft_printf("x[%d]: %x\n", i, x[i++]);
#endif
	FF (a, b, c, d, x[ 0], S11, 0xd76aa478);
	FF (d, a, b, c, x[ 1], S12, 0xe8c7b756);
	FF (c, d, a, b, x[ 2], S13, 0x242070db);
	FF (b, c, d, a, x[ 3], S14, 0xc1bdceee);
	FF (a, b, c, d, x[ 4], S11, 0xf57c0faf);
	FF (d, a, b, c, x[ 5], S12, 0x4787c62a);
	FF (c, d, a, b, x[ 6], S13, 0xa8304613);
	FF (b, c, d, a, x[ 7], S14, 0xfd469501);
	FF (a, b, c, d, x[ 8], S11, 0x698098d8);
	FF (d, a, b, c, x[ 9], S12, 0x8b44f7af);
	FF (c, d, a, b, x[10], S13, 0xffff5bb1);
	FF (b, c, d, a, x[11], S14, 0x895cd7be);
	FF (a, b, c, d, x[12], S11, 0x6b901122);
	FF (d, a, b, c, x[13], S12, 0xfd987193);
	FF (c, d, a, b, x[14], S13, 0xa679438e);
	FF (b, c, d, a, x[15], S14, 0x49b40821);

	/* Round 2 */
#ifdef DEBUG
	md5_debug(a, b, c, d);
	ft_printf("x[%d]: %x\n", i, x[i++]);
#endif
	GG (a, b, c, d, x[ 1], S21, 0xf61e2562);
	GG (d, a, b, c, x[ 6], S22, 0xc040b340);
	GG (c, d, a, b, x[11], S23, 0x265e5a51);
	GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa);
	GG (a, b, c, d, x[ 5], S21, 0xd62f105d);
	GG (d, a, b, c, x[10], S22, 0x02441453);
	GG (c, d, a, b, x[15], S23, 0xd8a1e681);
	GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8);
	GG (a, b, c, d, x[ 9], S21, 0x21e1cde6);
	GG (d, a, b, c, x[14], S22, 0xc33707d6);
	GG (c, d, a, b, x[ 3], S23, 0xf4d50d87);
	GG (b, c, d, a, x[ 8], S24, 0x455a14ed);
	GG (a, b, c, d, x[13], S21, 0xa9e3e905);
	GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8);
	GG (c, d, a, b, x[ 7], S23, 0x676f02d9);
	GG (b, c, d, a, x[12], S24, 0x8d2a4c8a);

	/* Round 3 */
#ifdef DEBUG
	md5_debug(a, b, c, d);
	ft_printf("x[%d]: %x\n", i, x[i++]);
#endif
	HH (a, b, c, d, x[ 5], S31, 0xfffa3942);
	HH (d, a, b, c, x[ 8], S32, 0x8771f681);
	HH (c, d, a, b, x[11], S33, 0x6d9d6122);
	HH (b, c, d, a, x[14], S34, 0xfde5380c);
	HH (a, b, c, d, x[ 1], S31, 0xa4beea44);
	HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9);
	HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60);
	HH (b, c, d, a, x[10], S34, 0xbebfbc70);
	HH (a, b, c, d, x[13], S31, 0x289b7ec6);
	HH (d, a, b, c, x[ 0], S32, 0xeaa127fa);
	HH (c, d, a, b, x[ 3], S33, 0xd4ef3085);
	HH (b, c, d, a, x[ 6], S34, 0x04881d05);
	HH (a, b, c, d, x[ 9], S31, 0xd9d4d039);
	HH (d, a, b, c, x[12], S32, 0xe6db99e5);
	HH (c, d, a, b, x[15], S33, 0x1fa27cf8);
	HH (b, c, d, a, x[ 2], S34, 0xc4ac5665);

	/* Round 4 */
#ifdef DEBUG
	md5_debug(a, b, c, d);
	ft_printf("x[%d]: %x\n", i, x[i++]);
#endif
	II (a, b, c, d, x[ 0], S41, 0xf4292244);
	II (d, a, b, c, x[ 7], S42, 0x432aff97);
	II (c, d, a, b, x[14], S43, 0xab9423a7);
	II (b, c, d, a, x[ 5], S44, 0xfc93a039);
	II (a, b, c, d, x[12], S41, 0x655b59c3);
	II (d, a, b, c, x[ 3], S42, 0x8f0ccc92);
	II (c, d, a, b, x[10], S43, 0xffeff47d);
	II (b, c, d, a, x[ 1], S44, 0x85845dd1);
	II (a, b, c, d, x[ 8], S41, 0x6fa87e4f);
	II (d, a, b, c, x[15], S42, 0xfe2ce6e0);
	II (c, d, a, b, x[ 6], S43, 0xa3014314);
	II (b, c, d, a, x[13], S44, 0x4e0811a1);
	II (a, b, c, d, x[ 4], S41, 0xf7537e82);
	II (d, a, b, c, x[11], S42, 0xbd3af235);
	II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb);
	II (b, c, d, a, x[ 9], S44, 0xeb86d391);
#ifdef DEBUG
	md5_debug(a, b, c, d);
	ft_printf("x[%d]: %x\n", i, x[i++]);
#endif

	ctx->regs[MD5_A] += a;
	ctx->regs[MD5_B] += b;
	ctx->regs[MD5_C] += c;
	ctx->regs[MD5_D] += d;

	ft_memset(&x, 0, sizeof(x));
}

void				md5_init(t_md5 *ctx)
{
	ctx->byte_count = 0;
	ft_memset(ctx->buf, 0, MD5_BUFFER_SIZE);
	ctx->regs[MD5_A] = 0x67452301;
	ctx->regs[MD5_B] = 0xefcdab89;
	ctx->regs[MD5_C] = 0x98badcfe;
	ctx->regs[MD5_D] = 0x10325476;
}

/*
void				md5_final(uint8_t *digest, t_md5 *ctx)
{}
*/

/*
**	MD5_BUFFER_SIZE: 64 bytes == 512 bits
**	0x3f == 63 == 0b111111
*/

void	md5(const uint8_t *msg, uint32_t len, uint32_t *digest)
{
	t_md5		ctx;
	int32_t		newlen;
	uint8_t		*data;
	int32_t		offset;
	uint8_t		*p;
	uint32_t	bits;
	uint32_t	digest_out[MD5_DIGEST_SIZE];

	(void)digest;
	if (msg == NULL || ft_strlen((char *)msg) == 0)
	{
		digest[0] = 0xd41d8cd9;
		digest[1] = 0x8f00b204;
		digest[2] = 0xe9800998;
		digest[3] = 0xecf8427e;
		return ;
	}
	md5_init(&ctx);
	newlen = len * 8;
	while (newlen % 512 != 448)
		++newlen;
	newlen /= 8;
	data = malloc(newlen + 64);
	ft_memset(data, '\0', newlen);
	ft_memcpy(data, msg, len);
	data[len] = 0x80; /* write 0x10000000 */
	bits = len * 8;
	memcpy(data + newlen, &bits, 4);/* len in bits at the end of the buf */
	offset = 0;
	p = data;

	while (offset < newlen)
	{
		md5_transform(&ctx, p);
		p = p + offset;
		offset += 512 / 8; /* 64 */
	}

	p = (uint8_t*)digest_out;
	p[ 0] = (ctx.regs[MD5_A] & 0xff000000) >> 24;
	p[ 1] = (ctx.regs[MD5_A] & 0x00ff0000) >> 16;
	p[ 2] = (ctx.regs[MD5_A] & 0x0000ff00) >> 8;
	p[ 3] = (ctx.regs[MD5_A] & 0x000000ff);
	p[ 4] = (ctx.regs[MD5_B] & 0xff000000) >> 24;
	p[ 5] = (ctx.regs[MD5_B] & 0x00ff0000) >> 16;
	p[ 6] = (ctx.regs[MD5_B] & 0x0000ff00) >> 8;
	p[ 7] = (ctx.regs[MD5_B] & 0x000000ff);
	p[ 8] = (ctx.regs[MD5_C] & 0xff000000) >> 24;
	p[ 9] = (ctx.regs[MD5_C] & 0x00ff0000) >> 16;
	p[10] = (ctx.regs[MD5_C] & 0x0000ff00) >> 8;
	p[11] = (ctx.regs[MD5_C] & 0x000000ff);
	p[12] = (ctx.regs[MD5_D] & 0xff000000) >> 24;
	p[13] = (ctx.regs[MD5_D] & 0x00ff0000) >> 16;
	p[14] = (ctx.regs[MD5_D] & 0x0000ff00) >> 8;
	p[15] = (ctx.regs[MD5_D] & 0x000000ff);

	ft_memcpy(digest, digest_out, MD5_DIGEST_SIZE*8);
}
