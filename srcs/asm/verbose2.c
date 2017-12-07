/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:44 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 13:33:39 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	verbose_arg_bis(char *line, int arg)
{
	int a;

	ft_printf("|");
	COLOR(C_BLUE);
	if (arg == T_DIR || arg == T_DIR4 || arg == T_LAB)
		ft_printf("%c", DIRECT_CHAR);
	else if (arg == T_REG)
		ft_printf("%c", REG_CHAR);
	a = 0;
	while (line[a] && !is_space(line[a]) && line[a] != SEPARATOR_CHAR)
	{
		ft_printf("%c", line[a]);
		++a;
	}
	COLOR(C_RESET);
	ft_printf("| ");
}

char	*swap_hex(char *str)
{
	int len;
	int a;
	int tmp;

	len = ft_strlen(str) - 1;
	a = 0;
	while (a < len)
	{
		tmp = str[len];
		str[len] = str[a + 1];
		str[a + 1] = tmp;
		tmp = str[len - 1];
		str[len - 1] = str[a];
		str[a] = tmp;
		len -= 2;
		a += 2;
	}
	return (str);
}
