/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:53:48 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 13:28:39 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_magic_nb(t_dasm_env *env)
{
	int		i;
	int		j;
	char	*hex;
	char	*tmp;
	char	*mag;

	mag = ft_conv_hex(ft_itoa(COREWAR_EXEC_MAGIC), HEX2);
	i = 0;
	j = 1;
	while (mag[i])
	{
		hex = ft_strndup(mag + i, 2);
		tmp = ft_convert_base(hex, HEX2, DEC);
		if (ft_atoi(tmp) != env->file[j])
			dasm_error(WRONG_MAG, NULL);
		++j;
		i += 2;
		ft_memdel((void*)&hex);
		ft_memdel((void*)&tmp);
	}
	ft_memdel((void*)&mag);
}

void	dasm_error(int err, char *str)
{
	COLOR(C_RED);
	ft_printf("Error: ");
	COLOR(C_RESET);
	if (err == SOURCE_ERR)
		ft_printf("Can't read source file %s.\n", str);
	else if (err == MALLOC_ERR)
		ft_printf("Malloc failed.\n");
	else if (err == OPEN_ERROR)
		ft_printf("Open error.\n");
	else if (err == SIZE_ERROR)
		ft_printf("Size too big.\n");
	else if (err == NAME_SIZE_ERR)
		ft_printf("Name size too big.\n");
	else if (err == COM_SIZE_ERR)
		ft_printf("Comments size too big.\n");
	else if (err == WRONG_FILE)
		ft_printf("\"%s\" : Wrong file.\n", str);
	else if (err == NO_COMP)
		ft_printf("Rly dude ? Don't touch my .cor !\n");
	else if (err == WRONG_MAG)
		ft_printf("Wrong magic number.\n");
	if (err != WRONG_FILE)
		exit(EXIT_FAILURE);
}
