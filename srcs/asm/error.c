/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by lchety            #+#    #+#             */
/*   Updated: 2017/10/19 05:03:04 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	asm_error(int err, char *str)
{//en cas d error afficher str et exit le programme
	switch (err)
	{
		case SOURCE_ERR:
			ft_printf("Can't read source file %s\n", str);
			break;
		case MALLOC_ERR:
			ft_printf("Error: malloc failed\n");
			break;
	}
	exit(EXIT_FAILURE);
}
