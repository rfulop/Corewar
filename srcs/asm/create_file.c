/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/06 23:12:19 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	create_file(t_asm_env *env, char *str)
{
	int		fd;
	int		len;
	char	*tmp;
	char	*name;

	len = ft_strlen(str) - 2;
	if (!(tmp = ft_strndup(str, len)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	if (!(name = (char*)malloc(sizeof(char) * (len + 4 + 1))))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	name[len + 4] = '\0';
	name = ft_strcpy(name, tmp);
	name = ft_strcat(name, ".cor");
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ft_memdel((void*)&name);
	ft_memdel((void*)&tmp);
	env->fd = fd;
}

int		check_name(char *str)
{
	int size;

	size = ft_strlen(str);
	if (size < 2)
		return (0);
	return (str[size - 2] == '.' && str[size - 1] == 's' ? 1 : 0);
}
