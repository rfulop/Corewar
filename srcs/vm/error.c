/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by lchety            #+#    #+#             */
/*   Updated: 2017/09/14 12:01:00 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(char *str)
{//en cas d error afficher str et exit le programme
	ft_putstr(str);
	exit(EXIT_FAILURE);
}
