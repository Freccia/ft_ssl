/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_wrap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:08:07 by lfabbro           #+#    #+#             */
/*   Updated: 2018/11/18 16:48:28 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

/*
** Need this because of different algorithms arguments types
*/

inline void		ssl_sha256_init(void *ctx)
{
	sha256_init((t_sha256 *)ctx);
}

inline void		ssl_sha256_update(void *ctx, const uint8_t *data, uint32_t len)
{
	sha256_update((t_sha256*)ctx, data, len);
}

inline void		ssl_sha256_final(void *ctx, uint32_t *hash)
{
	sha256_final((t_sha256*)ctx, hash);
}
