/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:03:04 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/08 20:34:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void		ssl_md5_init(void *ctx)
{
	md5_init((t_md5 *)ctx);
}

void		ssl_md5_update(void *ctx, const uint8_t *data, uint32_t len)
{
	md5_update((t_md5*)ctx, data, len);
}

void		ssl_md5_final(void *ctx, uint32_t *digest)
{
	md5_final((t_md5*)ctx, digest);
}
