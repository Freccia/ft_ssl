/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crypto_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:27:37 by lfabbro           #+#    #+#             */
/*   Updated: 2018/08/26 18:43:42 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

/*
uint8_t		*md5(uint8_t *msg, uint32_t len, uint8_t *dig);

void				md5_init(t_md5 *ctx);
void				md5_update(t_md5 *ctx);
void				m5_final(uint8_t *dig, t_md5 *ctx);
*/

/*
     //Process each 16-word block. 
     //For i = 0 to N/16-1 do

     Copy block i into X.
     For j = 0 to 15 do
       Set X[j] to M[i*16+j].
     end // of loop on j //

     // Save A as AA, B as BB, C as CC, and D as DD. //
     AA = A
     BB = B
     CC = C
     DD = D

     // Round 1. //
     // Let [abcd k s i] denote the operation
     //     a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). //
     // Do the following 16 operations. //

     [ABCD  0  7  1]  [DABC  1 12  2]  [CDAB  2 17  3]  [BCDA  3 22  4]
     [ABCD  4  7  5]  [DABC  5 12  6]  [CDAB  6 17  7]  [BCDA  7 22  8]
     [ABCD  8  7  9]  [DABC  9 12 10]  [CDAB 10 17 11]  [BCDA 11 22 12]
     [ABCD 12  7 13]  [DABC 13 12 14]  [CDAB 14 17 15]  [BCDA 15 22 16]

     // Round 2. //
     // Let [abcd k s i] denote the operation
     //   a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). //
     // Do the following 16 operations. //

     [ABCD  1  5 17]  [DABC  6  9 18]  [CDAB 11 14 19]  [BCDA  0 20 20]
     [ABCD  5  5 21]  [DABC 10  9 22]  [CDAB 15 14 23]  [BCDA  4 20 24]
     [ABCD  9  5 25]  [DABC 14  9 26]  [CDAB  3 14 27]  [BCDA  8 20 28]
     [ABCD 13  5 29]  [DABC  2  9 30]  [CDAB  7 14 31]  [BCDA 12 20 32]

     // Round 3. //
     // Let [abcd k s t] denote the operation
     //   a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s). //
     // Do the following 16 operations. //

     [ABCD  5  4 33]  [DABC  8 11 34]  [CDAB 11 16 35]  [BCDA 14 23 36]
     [ABCD  1  4 37]  [DABC  4 11 38]  [CDAB  7 16 39]  [BCDA 10 23 40]
     [ABCD 13  4 41]  [DABC  0 11 42]  [CDAB  3 16 43]  [BCDA  6 23 44]
     [ABCD  9  4 45]  [DABC 12 11 46]  [CDAB 15 16 47]  [BCDA  2 23 48]

     // Round 4. //
     // Let [abcd k s t] denote the operation
     //   a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s). //
     // Do the following 16 operations. //

     [ABCD  0  6 49]  [DABC  7 10 50]  [CDAB 14 15 51]  [BCDA  5 21 52]
     [ABCD 12  6 53]  [DABC  3 10 54]  [CDAB 10 15 55]  [BCDA  1 21 56]
     [ABCD  8  6 57]  [DABC 15 10 58]  [CDAB  6 15 59]  [BCDA 13 21 60]
     [ABCD  4  6 61]  [DABC 11 10 62]  [CDAB  2 15 63]  [BCDA  9 21 MD5_BUFFER_SIZE]

     // Then perform the following additions. (That is increment each
     // of the four registers by the value it had before this block
     // was started.) //

     A = A + AA
     B = B + BB
     C = C + CC
     D = D + DD

   end // of loop on i //
*/


// Decodes input (unsigned char) into output (uint32_t). Assumes len is
// a multiple of 4.
static void Decode( uint32_t *output, uint8_t *input, uint32_t len )
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
			(((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
}

/*
	x[0] = buf[0];
	x[1] = buf[1];
	x[2] = buf[2];
	x[3] = buf[3];
	x[4] = buf[4];
	x[5] = buf[5];
	x[6] = buf[6];
	x[7] = buf[7];
	x[8] = buf[8];
	x[9] = buf[9];
	x[10] = buf[10];
	x[11] = buf[11];
	x[12] = buf[12];
	x[13] = buf[13];
	x[14] = buf[14];
	x[15] = buf[15];
*/

void			md5_debug(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	uint8_t *p;
	p=(uint8_t *)&a;
	ft_printf("\nabcd: %x %x %x %x\n", a, b, c, d);
	ft_printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);
	p=(uint8_t *)&b;
	ft_printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);
	p=(uint8_t *)&c;
	ft_printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);
	p=(uint8_t *)&d;
	ft_printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
}

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

/*
	ft_printf("data: ");
	for (int k=0; k < 64; k++) {
		ft_printf("%x", ptr[k]);
	}
	ft_printf("\n");

	for (int k=0; k<16; k++) {
		ft_printf("x[%d] = %x\n", k, x[k]);
	}
*/

/*
# define FF(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + F(b,c,d) + x + t), s))
# define GG(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + G(b,c,d) + x + t), s))
# define HH(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + H(b,c,d) + x + t), s))
# define II(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + I(b,c,d) + x + t), s))

# define F(x, y, z)		((x & y) | (~x & z))
# define G(x, y, z)		((x & z) | (y & ~z))
# define H(x, y, z)		(x ^ y ^ z)
# define I(x, y, z)		(y ^ (x | ~z))

# define ROTATE_LEFT(x, n)		(((x) << (n)) | ((x) >> (32 - (n))))
*/

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
{
	
}
*/

/*
**	MD5_BUFFER_SIZE: 64 bytes == 512 bits
**	0x3f == 63 == 0b111111
*/

uint8_t				*md5(uint8_t *msg, uint32_t len,
											uint32_t digest[MD5_DIGEST_SIZE])
{
	t_md5		ctx;
	int32_t		newlen;
	uint8_t		*data;
	int32_t		offset;
	uint8_t		*p;
	uint32_t	bits;
	uint32_t	digest_out[MD5_DIGEST_SIZE];

	(void)digest;
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

	ft_printf("digout: %x%x%x%x  -\n", digest_out[0], digest_out[1],
			digest_out[2], digest_out[3]);

	ft_memcpy(digest, digest_out, MD5_DIGEST_SIZE*8);
	return (NULL);
}
