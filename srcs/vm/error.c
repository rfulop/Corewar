/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by lchety            #+#    #+#             */
/*   Updated: 2017/12/05 14:31:07 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		error(char *str)
{
	COLOR(C_RED);
	ft_printf("Error: ");
	COLOR(C_RESET);
	ft_putstr(str);
	exit(EXIT_FAILURE);
}
