/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:53:48 by rfulop            #+#    #+#             */
/*   Updated: 2017/10/27 03:44:05 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		print_dir4(int fd, unsigned char *str)
{
	int dir;

	dir = get_uint32(str);
	write(fd, "%", 1);
	ft_putnbr_fd(dir, fd);
	return (DIR_SIZE);
}

int		print_dir2(int fd, unsigned char *str)
{
	int dir;

	dir = get_uint16(str);
	write(fd, "%", 1);
	ft_putnbr_fd(dir, fd);
	return (IND_SIZE);
}

int		print_reg(int fd, int reg)
{
	write(fd, "r", 1);
	ft_putnbr_fd(reg, fd);
	return (REG_SIZE);
}

int		print_ind(int fd, unsigned char *str)
{
	int ind;

	ind = get_uint16(str);
	write(fd, " ", 1);
	ft_putnbr_fd(ind, fd);
	return (IND_SIZE);
}

int		print_args(int fd, int inst, unsigned char *file)
{
	int		i;
	int		j;
	char	args[3];

	i = 0;
	args[0] = *file >> 6;
	args[1] = *file >> 4 & 3;
	args[2] = *file >> 2 & 3;
	++i;
	j = 0;
	while (j < 3)
	{
		if (args[j] == DIR_CODE && (inst == 10 || inst == 11 || inst == 14))
			i += print_dir2(fd, file + i);
		else if (args[j] == REG_CODE)
			i += print_reg(fd, file[i]);
		else if (args[j] == DIR_CODE)
			i += print_dir4(fd, file + i);
		else if (args[j] == IND_CODE)
			i += print_ind(fd, file + i);
		++j;
		if (j < 3 && args[j])
			write(fd, ", ", 2);
	}
	return (i);
}
