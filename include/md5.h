/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:48:36 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/08 17:47:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include <stdint.h>

/*
** Using 32bits long ints for md5 operations
*/
typedef uint32_t	u32;

/* in bytes */
# define MD5_BUFFER_SIZE	64
# define MD5_DIGEST_SIZE	4  /* 4*32 = 128 bits*/

/*
** MD5 Basic Functions
*/
# define F(x, y, z)		((x & y) | (~x & z))
# define G(x, y, z)		((x & z) | (y & ~z))
# define H(x, y, z)		(x ^ y ^ z)
# define I(x, y, z)		(y ^ (x | ~z))

/*
** Rotates x left n bits.
*/
# define ROTATE_LEFT(x, n)		(((x) << (n)) | ((x) >> (32 - (n))))

/*
** FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
** Rotation is separate from addition to prevent recomputation.
*/
# define FF(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + F(b,c,d) + x + t), s))
# define GG(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + G(b,c,d) + x + t), s))
# define HH(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + H(b,c,d) + x + t), s))
# define II(a,b,c,d,x,s,t)	(a = b + ROTATE_LEFT((a + I(b,c,d) + x + t), s))

/*
** MD5 Context
*/
# define S11			7
# define S12			12
# define S13			17
# define S14			22
# define S21			5
# define S22			9
# define S23			14
# define S24			20
# define S31			4
# define S32			11
# define S33			16
# define S34			23
# define S41			6
# define S42			10
# define S43			15
# define S44			21

/*
** MD5 Registers
*/
# define MD5_A			0
# define MD5_B			1
# define MD5_C			2
# define MD5_D			3

/*
**	bitcount: bits already parsed (bitcount[1] for overflow)
**	regs: registers (A,B,C,D) for operations
**	buff: buffer for md5 operations (512 bits long -> 8*64)
*/
typedef struct		s_md5_ctx {
	uint32_t		regs[4];
	uint32_t		bitcount[2];
	uint8_t			buff[MD5_BUFFER_SIZE];
}					t_md5;

/*
** MD5 FUNCTIONS
** (ctx = md5_context; dig = digest; data = data to cypher)
*/
void md5(const uint8_t *msg, uint32_t len, uint32_t *dig);
int  md5_file (const char *filename);

void				md5_init(t_md5 *ctx);
void				md5_pad(t_md5 *ctx);
void				md5_update(t_md5 *ctx, const uint8_t *data, uint32_t len);
void				md5_final(uint32_t digest[MD5_DIGEST_SIZE], t_md5 *ctx);

#endif
