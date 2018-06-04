/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:14:33 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/04 19:59:35 by rbaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static t_bool	sizes_check(void)
{
	if (IND_SIZE < 1 || sizeof(intmax_t) < IND_SIZE)
		bug_err("Wrong define value in op.h: IND_SIZE\n");
	if (DIR_SIZE < 1 || sizeof(intmax_t) < DIR_SIZE)
		bug_err("Wrong define value in op.h: DIR_SIZE\n");
	if (REG_SIZE < 1 || sizeof(intmax_t) < REG_SIZE)
		bug_err("Wrong define value in op.h: REG_SIZE\n");
	return (TRUE);
}

/*
** @desc assert if labels datas
**       is pure.
** @params i iterators
** @return Bool[Success];
*/

static t_bool	labels_check(const char *labels,
					uint_fast32_t i)
{
	while (labels[i] != '\0')
	{
		if (labels[i] == LABEL_CHAR)
			bug_err("Inconsistency in op.h between labels & LABEL_CHAR\n");
		if (labels[i] == COMMENT_CHAR)
			bug_err("Inconsistency in op.h between labels & COMMENT_CHAR\n");
		if (labels[i] == DIRECT_CHAR)
			bug_err("Inconsistency in op.h between labels & DIRECt_CHAR\n");
		if (labels[i] == SEPARATOR_CHAR)
			bug_err("Inconsistency in op.h between labels & SEPARATOR_CHAR\n");
		if (labels[i] == EOL)
			bug_err("Inconsistency in op.h between labels & EOL\n");
		if (ft_strchr(WHITESPACE, labels[i]))
			bug_err("Inconsistency in op.h between labels & WHITESPACE\n");
		if (labels[i] == MINUS)
			bug_err("Inconsistency in op.h between labels & MINUS\n");
		if (labels[i] == STRING_CHAR)
			bug_err("Inconsistency in op.h between labels & STRING_CHAR\n");
		i++;
	}
	return (TRUE);
}

/*
** @desc assert if labels datas
**       is pure.
** @params i iterators
** @return Bool[Success];
*/

static t_bool	base_check(const char *base,
					uint_fast32_t i)
{
	while (base[i] != '\0')
	{
		if (base[i] == LABEL_CHAR)
			bug_err("Inconsistency in op.h between base & LABEL_CHAR\n");
		if (base[i] == COMMENT_CHAR)
			bug_err("Inconsistency in op.h between base & COMMENT_CHAR\n");
		if (base[i] == DIRECT_CHAR)
			bug_err("Inconsistency in op.h between base & DIRECT_CHAR\n");
		if (base[i] == SEPARATOR_CHAR)
			bug_err("Inconsistency in op.h between base & SEPARATOR_CHAR\n");
		if (base[i] == EOL)
			bug_err("Inconsistency in op.h between base & EOL\n");
		if (ft_strchr(WHITESPACE, base[i]))
			bug_err("Inconsistency in op.h between base & WHITESPACE\n");
		if (base[i] == MINUS)
			bug_err("Inconsistency in op.h between base & MINUS\n");
		if (base[i] == STRING_CHAR)
			bug_err("Inconsistency in op.h between base & STRING_CHAR\n");
		i++;
	}
	return (TRUE);
}

/*
** @desc init function to assert
**       if the define set is correct
**       for processing;
** @params i iterators
** @return Bool[Success];
*/

t_bool			check_collisions(const char *base, const char *labels)
{
	if (!(labels_check(labels, 0)) || !(base_check(base, 0)) || !sizes_check())
		return (FALSE);
	return (TRUE);
}
