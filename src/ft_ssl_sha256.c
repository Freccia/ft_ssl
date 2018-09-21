/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 10:20:55 by lfabbro           #+#    #+#             */
/*   Updated: 2018/09/21 10:42:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void		ssl_sha256_init(void *ctx)
{
	sha256_init((t_sha256 *)ctx);
}

void		ssl_sha256_update(void *ctx, const uint8_t *data, uint32_t len)
{
	sha256_update((t_sha256*)ctx, data, len);
}

void		ssl_sha256_final(void *ctx, uint32_t *digest)
{
	sha256_final((t_sha256*)ctx, digest);
}
