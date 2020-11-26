/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:40:04 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:33:58 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct
{
	int			flags;
	int			nbr_f;
	int			p;
	int			nbr_p;
	int			conv;
	int			fd;
	size_t		c;
}				t_flags;

void			ft_check_struct2(t_flags *prt, va_list args);
void			ft_check_struct(t_flags *prt, va_list args);

void			ft_conv(t_flags *prt, va_list args);

void			ft_flags_m(t_flags *prt, va_list args);

void			ft_flag_z(t_flags *prt, va_list args);

void			ft_just_flag(t_flags *prt, va_list args);
void			ft_full_flags_m(t_flags *prt, va_list args);
void			ft_full_flags(t_flags *prt, va_list args);

int				ft_count_nbr(const char *str, int *i);
int				ft_intlen(int n);
int				pt_strlen(char *str);
int				ft_unsigned_len(unsigned int nb);
int				ft_hexa_len(unsigned int nb);

t_flags			*ft_is_stars(int *i, t_flags *prt, va_list args);
t_flags			*ft_is_p(const char *str, int *i, t_flags *prt, va_list args);
t_flags			*ft_is_flags(const char *str, int *i, t_flags *prt);
t_flags			*ft_parse_conv(const char *str, int *i, t_flags *prt);
void			ft_parse(const char *str, int *i, va_list args, t_flags *prt);

void			ft_percent_right(t_flags *prt);
void			ft_percent_left(t_flags *prt, char q);

void			ft_precision(t_flags *prt, va_list args);

void			ft_c_right(t_flags *prt, va_list args);
void			ft_c_left(t_flags *prt, char q, va_list args);

int				*ft_print_m(int *u, t_flags *prt);
void			ft_putchar_c(char u, t_flags *prt);
void			ft_putstr_c(char *str, t_flags *prt);
char			*ft_strcpy(char *dst, char *src);

void			ft_di_width_p(t_flags *prt, va_list args);
void			ft_di_left_p(t_flags *prt, char q, va_list args);
void			ft_di_right(t_flags *prt, va_list args);
void			ft_di_left(t_flags *prt, char q, va_list args);
void			ft_di_truc(t_flags *prt, int len, int nbr);

void			ft_maj_x_width_p(t_flags *prt, va_list args);
void			ft_maj_x_l_p(t_flags *prt, char q, va_list args);
void			ft_maj_x_right(t_flags *prt, va_list args);
void			ft_maj_x_l(t_flags *prt, char q, va_list args);
void			ft_maj_x_truc(t_flags *prt, int len);

void			ft_putnbr_hexa(unsigned int n, t_flags *prt);
void			ft_putnbru(unsigned int n, t_flags *prt);
void			ft_putnbrdi(int n, t_flags *prt);
void			ft_putnbr_hexa_maj(unsigned int n, t_flags *prt);
void			ft_putnbr_p(unsigned long long n, t_flags *prt);

int				ft_p_len(unsigned long long nb);
void			ft_adres(unsigned long long nb, t_flags *prt);
void			ft_p_right(t_flags *prt, va_list args);
void			ft_p_left(t_flags *prt, char q, va_list args);

void			ft_s_l_space(t_flags *prt, char q, va_list args);
void			ft_s_right(t_flags *prt, va_list args);
void			ft_s_lz(t_flags *prt, va_list args);

void			ft_u_left(t_flags *prt, char q, va_list args);
void			ft_u_right(t_flags *prt, va_list args);
void			ft_u_left_p(t_flags *prt, char q, va_list args);
void			ft_u_width_p2(t_flags *prt, int len);
void			ft_u_width_p(t_flags *prt, va_list args);

void			ft_x_l(t_flags *prt, char q, va_list args);
void			ft_x_right(t_flags *prt, va_list args);
void			ft_x_l_p(t_flags *prt, char q, va_list args);
void			ft_x_width_p2(t_flags *prt, int len);
void			ft_x_width_p(t_flags *prt, va_list args);

t_flags			fill_struct(t_flags *prt, int fd);
int				ft_fprintf(int fd, const char *list, ...);
void			ft_s_wp2(t_flags *prt, char *str);
void			ft_s_wp3(t_flags *prt, int len, char *str);
void			ft_s_wp(t_flags *prt, va_list args);

void			ft_s_lz_p2(t_flags *prt);
void			ft_s_lz_p(t_flags *prt, va_list args);

void			ft_s_w_p2(t_flags *prt, int i, char *str);
void			ft_s_w_p3(t_flags *prt, int i, char *str);
void			ft_s_w_p(t_flags *prt, va_list args);

void			ft_width(t_flags *prt, va_list args);
void			ft_width_p(t_flags *prt, va_list args);

#endif
