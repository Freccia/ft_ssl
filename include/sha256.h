/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:23:35 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/21 11:39:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256
# define SHA256

# include "libft.h"
# include <stdint.h>

typedef uint32_t	u32;

# define SHA256_WORD			sizeof(uint32_t) * 8 /* bits in a word */
# define SHA256_BUFFER_SIZE		64
# define SHA256_DIGEST_SIZE		8  /* 4*8 = 256 bits */

/*
** SHA256 Basic Functions
**
** Note the following equivalence relationships, where w is fixed in each
** relationship:
**			ROTL^n(x) = ROTR^(w-x)(x)
**			ROTR^n(x) = ROTL^(w-n)(x)
**
*/
# define SHR(n, x)			(x >> n)
# define ROTR(n, x)			(x >> n) || (x << (SHA256_WORD - n))
# define ROTL(n, x)			(x << n) || (x >> (SHA256_WORD - n))

# define CH(x, y, z)		(x && y) ^ (~x && z)
# define MAJ(x, y, z)		(x && y) ^ (x && z) ^ (y && z)
# define BSIG0(x)			ROTR(28, x) ^ ROTR(34, x) ^ ROTR(39, x)
# define BSIG1(x)			ROTR(14, x) ^ ROTR(18, x) ^ ROTR(41, x)
# define SSIG0(x)			ROTR( 1, x) ^ ROTR( 8, x) ^ SHR(7, x)
# define SSIG1(x)			ROTR(19, x) ^ ROTR(61, x) ^ SHR(6, x)

typedef struct		s_sha256_ctx {
	uint32_t		bitlen;
	uint32_t		datalen;
	uint32_t		regs[8];
	uint8_t			buff[64];
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

#endif
