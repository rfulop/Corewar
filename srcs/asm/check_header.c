/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:31:44 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/04 17:36:53 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_header_form(t_asm_env *env, char *line)
{
	int i;
	int len;

	i = until_is_space(line);
	i += until_is_not_space(line + i);
	if (line[i] != '\"')
	{
		asm_error(WRONG_FORM_COM, NULL, env, i);
		return (0);
	}
	len = 0;
	++i;
	while (line[i + len] && line[i + len] != '\"')
	{
		if (line[i + len] == '\"')
			break ;
		++len;
	}
	if (!len || line[i + len + 1] != '\0')
		asm_error(WRONG_FORM_COM, NULL, env, i + len);
	else if (line[i + len] == '\"')
		return (len);
	else
		asm_error(WRONG_FORM_COM, NULL, env, i);
	return (0);
}

void	check_header_name(t_asm_env *env, int len)
{
	if (env->name)
		asm_error(NAME_EXISTS, NULL, env, 0);
	else if (len > PROG_NAME_LENGTH)
		asm_error(NAME_SIZE_ERR, NULL, env, 0);
	if (!env->ko)
		++env->name;
}

void	check_header_com(t_asm_env *env, int len)
{
	if (env->comment)
		asm_error(COM_EXISTS, NULL, env, 0);
	else if (len > COMMENT_LENGTH)
		asm_error(COM_SIZE_ERR, NULL, env, 0);
	if (!env->ko)
		++env->comment;
}

void	check_header(t_asm_env *env, char *line)
{
	char	*word;
	int		len;

	word = take_word(line);
	len = check_header_form(env, line);
	if (!ft_strcmp(word, NAME_CMD_STRING))
		check_header_name(env, len);
	else if (!ft_strcmp(word, COMMENT_CMD_STRING))
		check_header_com(env, len);
	else if (len)
		asm_error(COMMAND_ERR, word, env, 0);
	ft_memdel((void*)&word);
}
