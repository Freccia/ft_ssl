/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crypto_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:27:37 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/25 16:32:42 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

/*
unsigned char		*md5(unsigned char *msg, t_int_md5 len, unsigned char *dig);

void				md5_init(t_md5_ctx *ctx);
void				md5_update(t_md5_ctx *ctx);
void				m5_final(unsigned char *dig, t_md5_ctx *ctx);
*/
static unsigned char md5_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char		*md5(unsigned char *msg, t_int_md5 len,
						unsigned char *digest)
{
	(void)md5_padding;
	(void)msg;
	(void)len;
	(void)digest;
	t_md5_ctx		ctx;

	ctx.size = 0;
	ctx.bits = 0;
	ctx.regs[MD5_A] = 0x67452301;
	ctx.regs[MD5_B] = 0xefcdab89;
	ctx.regs[MD5_C] = 0x98badcfe;
	ctx.regs[MD5_D] = 0x10325476;
	return (NULL);
}
