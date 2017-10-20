/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/10/13 15:59:31 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_optab	op_tab[17] =
{
	{"live", &live, 1, T_DIR, 1, 10, "alive", 0, 0},
	{"ld", &ld, 2, {0,0,0}, 2, 5, "load", 1, 0},
	{"st", &st, 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", &add, 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", &sub, 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", &and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", &or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", &xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", &zjmp, 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", &ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", &sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", &ft_fork, 1, T_DIR, 12, 800, "fork", 0, 1},
	{"lld", NULL, 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", NULL, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", NULL, 1, T_DIR, 15, 1000, "long fork", 0, 1},
	{"aff", NULL, 1, T_REG, 16, 2, "aff", 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};
