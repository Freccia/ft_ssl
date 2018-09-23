/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:23:35 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/23 12:38:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256
# define SHA256

# include "libft.h"
# include <stdint.h>

typedef uint32_t	u32;

# define SHA256_WORD			sizeof(uint32_t) * 8 /* bits in a word */
# define SHA256_BUFFER_SIZE		64
# define SHA256_DIGEST_SIZE		8  /* 32*8 = 256 bits */

/*
** SHA256 Basic Functions
**
** Note the following equivalence relationships, where w is fixed in each
** relationship:
**			ROTL^n(x) = ROTR^(w-x)(x)
**			ROTR^n(x) = ROTL^(w-n)(x)
**
*/
# define SHR(x, n)			((x) >> (n))
# define ROTL(x, n)			(((x) << (n)) | ((x) >> (32 - (n))))
# define ROTR(x, n)			(((x) >> (n)) | ((x) << (32 - (n))))

# define CH(x, y, z)		(((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z)		(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define BSIG0(x)				(ROTR(x,  2) ^ ROTR(x, 13) ^ ROTR(x, 22))
# define BSIG1(x)				(ROTR(x,  6) ^ ROTR(x, 11) ^ ROTR(x, 25))
# define SSIG0(x)			(ROTR(x,  7) ^ ROTR(x, 18) ^ ((x) >>  3))
# define SSIG1(x)			(ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))


typedef struct		s_sha256_ctx {
	uint64_t		bitlen;
	uint32_t		datalen;
	uint32_t		regs[8];
	uint8_t			data[64];
}					t_sha256;

typedef struct		s_transform_ctx {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		t1;
	uint32_t		t2;
	uint32_t		m[64];

}					t_transform_ctx;

void		sha256_init(t_sha256 *ctx);
void		sha256_update(t_sha256 *ctx, const uint8_t data[], uint32_t len);
void		sha256_transform(t_sha256 *ctx, const uint8_t data[]);
void		sha256_final(t_sha256 *ctx, uint8_t hash[]);

#endif
