/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:45:40 by lfabbro           #+#    #+#             */
/*   Updated: 2018/11/17 15:52:40 by lfabbro          ###   ########.fr       */
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

# define N_CYPHERS		2

/*
** SSL Cypher Options
*/
# define SSL_OPTIONS	"hpqrs:"
# define SSL_OPT_P		1
# define SSL_OPT_Q		2
# define SSL_OPT_R		4
# define SSL_OPT_S		8
# define SSL_OPT_END	16

typedef struct		s_ssl_cypher
{
	char			name[8];
	char			cy_name[8];
	uint64_t		ctx_size;
	void			(*cy_string)(const char *msg, int opt);
	void			(*cy_filter)(int quiet);
	int				(*cy_files)(int ac, char **av, int opt);
}					t_ssl_cypher;

typedef struct		s_ssl_ctx
{
	int64_t			opt;
	t_ssl_cypher	cypher[N_CYPHERS];
}					t_ssl_ctx;

/*
** FT_SSL TOOL FUNCTIONS
*/
uint64_t			ft_ssl_strlen(const char *msg);

/*
** FT_SSL FUNCTIONS
*/
int					ft_ssl(int ac, char **av, t_ssl_cypher *chyphr);

#endif
