/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:42:55 by lfabbro           #+#    #+#             */
/*   Updated: 2018/11/18 16:48:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_ssl.h"

/*
** Need this because of different algorithms arguments types
*/

inline void		ssl_md5_init(void *ctx)
{
	md5_init((t_md5 *)ctx);
}

inline void		ssl_md5_update(void *ctx, const uint8_t *data, uint32_t len)
{
	md5_update((t_md5*)ctx, data, len);
}

inline void		ssl_md5_final(void *ctx, uint32_t *digest)
{
	md5_final((t_md5*)ctx, digest);
}
