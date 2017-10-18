/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 19:23:36 by rfulop            #+#    #+#             */
/*   Updated: 2017/04/29 03:19:20 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_b(va_list ap, t_opt *opt)
{
	char			*str;
	unsigned int	b;

	b = va_arg(ap, unsigned int);
	str = ft_convert_base(ft_itoa(b), DEC, BIN);
	write(1, str, (int)ft_strlen(str));
	opt->len += (int)ft_strlen(str);
	free(str);
}
