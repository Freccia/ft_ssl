/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:20:38 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/25 12:14:20 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "libft.h"
# include "getopt.h"
# include <stdint.h>

/*
** Using 32bits long ints
*/
typedef uint32_t	t_md5_int;

# define MD5_OPTIONS	"-hpqrs"
# define MD5_BUFFER		1024

/*
** MD5 OPTIONS
*/
# define MD5_OPT_P		1
# define MD5_OPT_Q		2
# define MD5_OPT_R		4
# define MD5_OPT_S		8
# define MD5_A			regs.a
# define MD5_B			regs.b
# define MD5_C			regs.c
# define MD5_D			regs.d

/*
** MD5 Context
*/
typedef struct		s_reg {
	int				a;
	int				b;
	int				c;
	int				d;
}					t_reg;

typedef struct		s_md5_ctx {
	t_reg			regs;
	unsigned char	*buf;
	t_md5_int		size;
	t_md5_int		bits;
}					t_md5_ctx;

/*
** MD5 FUNCTIONS
** (ctx = md5_context; dig = digest; msg = message to cypher)
*/
unsigned char		*md5(unsigned char *msg, t_md5_int len, unsigned char *dig);

void				md5_init(t_md5_ctx *ctx);
void				md5_update(t_md5_ctx *ctx);
void				m5_final(unsigned char *dig, t_md5_ctx *ctx);

#endif
