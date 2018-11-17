/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:48:36 by lfabbro           #+#    #+#             */
/*   Updated: 2018/10/04 16:29:41 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include <stdint.h>

/*
** in bytes
*/
# define MD5_BUFFER_SIZE	64
# define MD5_DIGEST_SIZE	4

/*
** 4*32 = 128 bits
*/

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
# define A				0
# define B				1
# define C				2
# define D				3

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
** MD5 CORE
*/
void				md5_init(t_md5 *ctx);
void				md5_update(t_md5 *ctx, const uint8_t *data, uint32_t len);
void				md5_final(t_md5 *ctx, uint32_t digest[]);

/*
** F*ING NORME !
*/
void				md5_transform_round_one(uint32_t *regz, uint32_t x[16]);
void				md5_transform_round_two(uint32_t *regz, uint32_t x[16]);
void				md5_transform_round_three(uint32_t *regz, uint32_t x[16]);
void				md5_transform_round_four(uint32_t *regz, uint32_t x[16]);
void				encode(uint8_t *out, uint32_t *in, unsigned int len);
void				decode(uint32_t *out, const uint8_t *in, uint32_t len);

/*
** SHA256 WRAPPERS
*/
void				ssl_md5_init(void *ctx);
void				ssl_md5_update(void *ctx, const uint8_t *dat, uint32_t len);
void				ssl_md5_final(void *ctx, uint32_t *digest);

int					md5_file (const char *filename, uint32_t digest[]);
void				md5_string(const char *msg, int opt);
void				md5_data(const uint8_t *msg, uint32_t len, uint32_t dig[]);
void				md5_filter(int quiet);
int					md5_files(int ac, char **av, int opt);

#endif
