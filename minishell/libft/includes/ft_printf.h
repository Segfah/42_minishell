/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 08:19:18 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:30:51 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct	s_ptf
{
	int			maximus;
	int			max;
	int			minus;
	int			min;
	int			zero;
	int			zer;
	int			precision;
	int			pre;
	char		typ;
	int			tmp;
	int			nul;
}				t_ptf;

char			*ft_check_wid(char *str, va_list ap, t_ptf *node);
char			*ft_check_max(char *str, va_list ap, t_ptf *node);
char			*ft_check_min(char *str, va_list ap, t_ptf *node);
char			*ft_check_pres(char *str, va_list ap, t_ptf *node);
char			*ft_check_zero(char *str, va_list ap, t_ptf *node);

int				ft_printf(const char *format, ...);

void			ft_ini_node(t_ptf *node);
int				ft_is_type(char c);
int				ft_is_flag(char c);
int				ft_putprintf(t_ptf *node, va_list ap);

int				ft_write_char(t_ptf *node, va_list ap);

int				ft_write_string(t_ptf *node, va_list ap);

int				ft_write_number(t_ptf *node, va_list ap, int res);
int				ft_write_number_minus(t_ptf *node, char *str);
int				ft_write_number_max(t_ptf *node, char *str);
int				ft_write_number_zero(t_ptf *node, char *str);
int				ft_write_number_zero_pres(t_ptf *node, char *str);

int				ft_write_hexa(t_ptf *node, va_list ap);

int				ft_write_pointer(t_ptf *node, va_list ap);
#endif
