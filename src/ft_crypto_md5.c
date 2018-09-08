/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crypto_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:27:37 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/08 18:30:25 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

#ifdef DEBUG
#include <stdio.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void		md5_transform(uint32_t regs[4], const uint8_t block[64]);

/*
** Decodes input (unsigned char) into output (uint32_t). Assumes len is
** a multiple of 4.
** Convert to big endian
*/
static void		decode(uint32_t *output, const uint8_t *input, uint32_t len)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((uint32_t)input[j])
					| (((uint32_t)input[j + 1]) << 8)
					| (((uint32_t)input[j + 2]) << 16)
					| (((uint32_t)input[j + 3]) << 24);
		++i;
		j += 4;
	}
}

/*
** Encodes input (uint32_t) into output (unsigned char). Assumes len is
** a multiple of 4.
** Convert to little endian
** Encodes input (UINT4) into output (unsigned char). Assumes len is
** a multiple of 4.
*/
static void encode( uint8_t *output, uint32_t *input, unsigned int len )
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (uint8_t)(input[i] & 0xff);
		output[j+1] = (uint8_t)((input[i] >> 8) & 0xff);
		output[j+2] = (uint8_t)((input[i] >> 16) & 0xff);
		output[j+3] = (uint8_t)((input[i] >> 24) & 0xff);
	}
}

int		md5_file(const char *filename, uint32_t *digest)
{
	t_md5			ctx;
	int				fd;
	int				len;
	unsigned char	buffer[1024];

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%s can't be opened\n", filename);
		return (EXIT_FAILURE);
	}
	md5_init(&ctx);
	while ((len = read(fd, buffer, 1024)))
	{
		md5_update(&ctx, buffer, len);
	}
	md5_final(digest, &ctx);
	close(fd);
	return (EXIT_SUCCESS);
}

void	md5_data(const uint8_t *msg, uint32_t len, uint32_t *dig)
{
	t_md5		ctx;
	uint32_t	parsed_len;

	md5_init(&ctx);
	parsed_len = 0;
	(void)len;
	//while (parsed_len < len) {
		md5_update(&ctx, msg + parsed_len, len);
	//	parsed_len += 64;
	//}
	md5_final(dig, &ctx);
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

	/* Set idx to number of bytes processed (bits/8) mod 64 (0x3F) */
	idx = (uint32_t)((ctx->bitcount[0] >> 3) & 0x3F);
	/* Update number of bits */
	/* If bitcount[0] overflow: bitcount[1]++ */
	if ((ctx->bitcount[0] += (uint32_t)datalen << 3) < ((uint32_t)datalen << 3))
		ctx->bitcount[1]++;
	/* If datalen overflow: (datalen << 3) >> 32) */
	ctx->bitcount[1] += ((uint32_t)datalen >> 29);
	partlen = 64 - idx;
	/* Transform block by block (64) */
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
	/* Copy into buffer remaining input */
	memcpy((void*)&ctx->buff[idx], (const void*)&data[i], datalen - i);
}

void			md5_pad(t_md5 *ctx)
{
	uint8_t		bits[8];
	uint32_t	idx;
	uint32_t	padlen;

	/* Save number of bits */
	ft_memset(bits, 0, 8);
	encode(bits, ctx->bitcount, 8);
	/* Pad out to 56 mod 64 */
	idx = (uint32_t)((ctx->bitcount[0] >> 3) & 0x3F);
	padlen = (idx < 56) ? (56 - idx) : (120 - idx);
	md5_update(ctx, PADDING, padlen);

	/* Append length (before padding) */
	md5_update(ctx, bits, 8);
}

/*
**	MD5_BUFFER_SIZE: 64 bytes == 512 bits
**	0x3f == 63 == 0b111111
*/
void			md5_final(uint32_t digest[MD5_DIGEST_SIZE], t_md5 *ctx)
{
	md5_pad(ctx);
	/* Store state in digest */
	encode((uint8_t*)digest, ctx->regs, 4);

	uint8_t		*p;
	p = (uint8_t*)digest;
	p[ 0] = (ctx->regs[MD5_A] & 0xff000000) >> 24;
	p[ 1] = (ctx->regs[MD5_A] & 0x00ff0000) >> 16;
	p[ 2] = (ctx->regs[MD5_A] & 0x0000ff00) >> 8;
	p[ 3] = (ctx->regs[MD5_A] & 0x000000ff);
	p[ 4] = (ctx->regs[MD5_B] & 0xff000000) >> 24;
	p[ 5] = (ctx->regs[MD5_B] & 0x00ff0000) >> 16;
	p[ 6] = (ctx->regs[MD5_B] & 0x0000ff00) >> 8;
	p[ 7] = (ctx->regs[MD5_B] & 0x000000ff);
	p[ 8] = (ctx->regs[MD5_C] & 0xff000000) >> 24;
	p[ 9] = (ctx->regs[MD5_C] & 0x00ff0000) >> 16;
	p[10] = (ctx->regs[MD5_C] & 0x0000ff00) >> 8;
	p[11] = (ctx->regs[MD5_C] & 0x000000ff);
	p[12] = (ctx->regs[MD5_D] & 0xff000000) >> 24;
	p[13] = (ctx->regs[MD5_D] & 0x00ff0000) >> 16;
	p[14] = (ctx->regs[MD5_D] & 0x0000ff00) >> 8;
	p[15] = (ctx->regs[MD5_D] & 0x000000ff);

#ifdef DEBUG
	ft_printf("%x%x%x%x\n", digest[0], digest[1], digest[2], digest[3]);
#endif
	/* Security: Zeroize sensitive information */
	ft_bzero(ctx, sizeof(t_md5));
}

#ifdef DEBUG
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
#endif

static void		md5_transform(uint32_t regs[4], const uint8_t block[64])
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	x[16];

	a = regs[MD5_A];
	b = regs[MD5_B];
	c = regs[MD5_C];
	d = regs[MD5_D];

	decode(x, block, 64);

#ifdef DEBUG
	for (int k=0; k<64; k++) {
		if ((k%16) == 1)
			printf("block[%d]: ", k);
		printf("%x ", block[k]);
		if (!(k%16))
			printf("\n");
	}
	printf("\n");
	printf("--\n");
	printf("x: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",
	x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10],x[11],x[12],x[13],x[14],x[15]);
#endif

	/* Round 1 */
#ifdef DEBUG
	int i = 0;
	md5_debug(a, b, c, d);
	printf("x[%d]: %x\n", i, x[i++]);
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
	printf("x[%d]: %x\n", i, x[i++]);
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
	printf("x[%d]: %x\n", i, x[i++]);
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
	printf("x[%d]: %x\n", i, x[i++]);
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
	printf("x[%d]: %x\n", i, x[i++]);
#endif

	regs[MD5_A] += a;
	regs[MD5_B] += b;
	regs[MD5_C] += c;
	regs[MD5_D] += d;

	ft_memset(&x, 0, sizeof(x));
}
