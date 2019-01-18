/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:45:40 by lfabbro           #+#    #+#             */
/*   Updated: 2019/01/18 15:31:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "getopt.h"
# include "error.h"
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define N_CIPHERS		3

/*
** SSL Cipher Options
*/
# define SSL_OPTIONS	"hpqrs:ed"
# define SSL_OPT_P		1
# define SSL_OPT_Q		2
# define SSL_OPT_R		4
# define SSL_OPT_S		8
# define SSL_OPT_ENC	16
# define SSL_OPT_DEC	32
# define SSL_OPT_END	64

typedef struct		s_ssl_cipher
{
	char			name[8];
	char			ci_name[8];
	uint64_t		ctx_size;
	char			*(*ci_getopt)(int ac, char **av, struct s_ssl_cipher *ci,
		int64_t *opt);
	void			(*ci_string)(const char *msg, int opt);
	void			(*ci_filter)(int quiet);
	int				(*ci_files)(int ac, char **av, int opt);
}					t_ssl_cipher;

typedef struct		s_ssl_ctx
{
	int64_t			opt;
	t_ssl_cipher	cipher[N_CIPHERS];
}					t_ssl_ctx;

/*
** FT_SSL TOOL FUNCTIONS
*/
uint64_t			ft_ssl_strlen(const char *msg);

/*
** FT_SSL FUNCTIONS
*/
int					ft_ssl(int ac, char **av, t_ssl_cipher *ci);
int					ft_ssl_getcipher(int ac, char **av, t_ssl_ctx *ctx);
void				ft_ssl_init_ctx(t_ssl_ctx *ctx);

#endif
