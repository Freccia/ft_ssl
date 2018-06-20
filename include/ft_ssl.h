/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:45:40 by lfabbro           #+#    #+#             */
/*   Updated: 2018/06/20 19:42:46 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "getopt.h"
# include <stdint.h>

# define MD5_OPTIONS		"hpqrs"

/*
** Do NOT use 1 as value in SSL_CYPH_* as it will conflicts with RETURN_FAILURE
*/
# define SSL_CYPH_MD5		2
# define SSL_CYPH_SHA1		4
# define SSL_CYPH_SHA256	8

typedef struct			s_ssl_ctx
{
	int64_t				opt;
	int32_t				cypher;
}						t_ssl_ctx;

/*
** FT_SSL FUNCTIONS
*/
int						ft_ssl_md5(int ac, char **av);
int						ft_ssl_md5_getopt(int ac, char **av, int64_t *opt);

#endif
