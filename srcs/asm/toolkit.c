/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/05 13:43:20 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		reverse_int(int nb)
{
	return (nb & 0x000000FFU) << 24 | (nb & 0x0000FF00U) << 8 |
	(nb & 0x00FF0000U) >> 8 | (nb & 0xFF000000U) >> 24;
}

short	reverse_short(short nb)
{
	return ((nb & 0xFFU) << 8 | (nb & 0xFF00U) >> 8);
}

int		is_dir_int(int i)
{
	return ((i == 1 || i == 2 || i == 6 || i == 7 || i == 8 || i == 13) ?
	1 : 0);
}

int		is_space(char c)
{
	return (c == ' ' || c == '\t' ? 1 : 0);
}

char	*take_word(char *str)
{
	int		a;
	int		len;
	char	*word;

	a = 0;
	len = 0;
	while (str[len] && !is_space(str[len]) && str[len] != SEPARATOR_CHAR)
		++len;
	if (!(word = (char*)malloc(sizeof(char) * len + 1)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	word[len] = '\0';
	while (a != len)
	{
		word[a] = str[a];
		++a;
	}
	return (word);
}
