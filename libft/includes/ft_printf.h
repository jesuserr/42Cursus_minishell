/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:35:36 by jesuserr          #+#    #+#             */
/*   Updated: 2023/02/13 10:38:34 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define HEX_LOWER	    "0123456789abcdef"
# define HEX_UPPER	    "0123456789ABCDEF"
# define POINTER_LOW	"0x"
# define POINTER_UPP	"0X"

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              HEADERS
*/
# include <unistd.h>
# include <stdarg.h>

/*
** -.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-
**                              FUNCTION PROTOTYPES
*/
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_put_number(long long n, int *i, char p_holder);
int		ft_put_num_hex(unsigned long long n, char p_holder, int ptr, int *i);
int		ft_printf(char const *hold, ...);

#endif