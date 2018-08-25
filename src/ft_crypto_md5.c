/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crypto_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:27:37 by lfabbro           #+#    #+#             */
/*   Updated: 2018/08/25 16:37:30 by lfabbro          ###   ########.fr       */
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
static void			md5_transform(t_md5 *ctx)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	*x;

	a = ctx->regs[MD5_A];
	b = ctx->regs[MD5_B];
	c = ctx->regs[MD5_C];
	d = ctx->regs[MD5_D];

	x = ctx->buf;

	/* Round 1 */
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

	ctx->regs[MD5_A] += a;
	ctx->regs[MD5_B] += b;
	ctx->regs[MD5_C] += c;
	ctx->regs[MD5_D] += d;
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
**	MD5_BUFFER_SIZE: 64 bytes == 512 bits
**	0x3f == 63 == 0b111111
*/

void				md5_update(t_md5 *ctx, const uint8_t *msg, uint32_t len)
{
	const uint32_t avail = sizeof(ctx->buf) - (ctx->byte_count & 0x3f);

	ctx->byte_count += len;
	if (avail > len)
	{
		ft_memcpy((char*)ctx->buf + (sizeof(ctx->buf) - avail), msg, len);
		return ;
	}
	ft_memcpy((char *)ctx->buf + (sizeof(ctx->buf) - avail), msg, avail);
	md5_transform(ctx);
	msg += avail;
	len -= avail;
	while (len > MD5_BUFFER_SIZE)
	{
		ft_memcpy(ctx->buf, msg, MD5_BUFFER_SIZE);
		md5_transform(ctx);
		msg += avail;
		len -= avail;
	}
	ft_memcpy(ctx->buf, msg, len);
}

void				md5_final(uint32_t *digest, t_md5 *ctx)
{
	const unsigned int offset = ctx->byte_count & 0x3f;
	char *p = (char *)ctx->buf + offset;
	int padding = 56 - (offset + 1);

	*p++ = 0x80;
	if (padding < 0) {
		ft_memset(p, 0x00, padding + sizeof (uint64_t));
		md5_transform(ctx);
		p = (char *)ctx->buf;
		padding = 56;
	}
	ft_memset(p, 0, padding);
	ctx->buf[14] = ctx->byte_count << 3;
	ctx->buf[15] = ctx->byte_count >> 29;
	md5_transform(ctx);
	//ft_memcpy(digest, ctx->hash, sizeof(mctx->hash));
	digest[0] = ctx->regs[MD5_A];
	digest[1] = ctx->regs[MD5_B];
	digest[2] = ctx->regs[MD5_C];
	digest[3] = ctx->regs[MD5_D];
	ft_memset(ctx, 0, sizeof(*ctx)); /* security override */

}

uint8_t				*md5(uint8_t *msg, uint32_t len, uint32_t *digest)
{
	(void)msg;
	(void)len;
	(void)digest;
	t_md5	ctx;

	md5_init(&ctx);
	//ft_strndup(ctx->msg, msg, ctx->len); // maybe we can avoid this operation
	md5_update(&ctx, msg, len);
	md5_final(digest, &ctx);
	return (NULL);
}
