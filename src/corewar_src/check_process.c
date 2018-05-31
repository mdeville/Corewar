/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeville <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:54:39 by mdeville          #+#    #+#             */
/*   Updated: 2018/05/31 17:28:52 by mdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

static t_bool	parse_reg(
							t_arena *arena,
							t_process *proc,
							size_t i)
{
	t_bool success;

	success = TRUE;
	if (!(proc->op.arg_type[i] & T_REG))
		success = FALSE;
	proc->param[i].type = REGISTER;
	vm_read(arena->memory, proc->pc + proc->offset,
			&proc->param[i].data.reg_nbr, 1);
	if (proc->param[i].data.reg_nbr <= 0
		|| proc->param[i].data.reg_nbr > REG_NUMBER)
		success = FALSE;
	++proc->offset;
	return (success);
}

static t_bool	parse_direct(
							t_arena *arena,
							t_process *proc,
							size_t i)
{
	t_bool success;
	t_bool index;

	success = TRUE;
	index = (proc->op.index) ? TRUE : FALSE;
	if (!(proc->op.arg_type[i] & T_DIR))
		success = FALSE;
	proc->param[i].type = DIRECT;
	vm_read(arena->memory, proc->pc + proc->offset,
			&proc->param[i].data, index ? IND_SIZE : DIR_SIZE);
	proc->offset += (index) ? IND_SIZE : DIR_SIZE;
	return (success);
}

static t_bool	parse_param(
							t_arena *arena,
							t_process *proc,
							unsigned char type,
							size_t index)
{
	t_bool success;

	success = TRUE;
	if (type == (REG_CODE << 6))
		success = parse_reg(arena, proc, index);
	else if (type == (DIR_CODE << 6))
		success = parse_direct(arena, proc, index);
	else if (type == (IND_CODE << 6))
	{
		if (!(proc->op.arg_type[index] & T_IND) || !vm_read(arena->memory,
		proc->pc + proc->offset, &proc->param[index].data.indirect, IND_SIZE))
			success = FALSE;
		proc->param[index].type = INDIRECT;
		proc->offset += IND_SIZE;
	}
	else
		success = FALSE;
	return (success);
}

static t_bool	set_params(t_arena *arena, t_process *proc)
{
	int				i;
	unsigned char	encoding_byte;
	t_bool			success;

	proc->offset = 1;
	if (!proc->op.coding_byte)
		encoding_byte = proc->op.arg_type[0] << 6;
	else
	{
		encoding_byte = arena->memory[(proc->pc + 1) % MEM_SIZE];
		++proc->offset;
	}
	success = TRUE;
	i = 0;
	while (i < proc->op.nb_param)
	{
		if (!parse_param(arena, proc, encoding_byte & 0XC0, i))
			success = FALSE;
		++i;
		encoding_byte <<= 2;
	}
	return (success);
}

/*
		else
		{
			ft_printf("Executing %s at %d with encoding_byte %#.8hhb and param ", proc->op.name, proc->pc, arena->memory[(proc->pc + 1) % MEM_SIZE]);
			int i = 0;
			while (i < proc->op.nb_param)
			{
				if (proc->op.index)
					ft_printf("%#.4hx ", proc->param[i].data.indirect);
				else
					ft_printf("%#.8x ", proc->param[i].data.direct);
				i++;
			}
			write(1, "\n", 1);
		}*/

void			check_process(t_arena *arena, t_dlist *elem)
{
	t_process *proc;

	proc = (t_process *)elem->content;
	if (arena->clock != proc->wait)
		return ;
	if (proc->instruction)
	{
		if (set_params(arena, proc))
			proc->instruction(arena, proc);
		proc->wait = arena->clock + 1;
		proc->instruction = NULL;
		return ;
	}
	if ((proc->pc = (proc->pc + proc->offset) % MEM_SIZE) < 0)
		proc->pc = MEM_SIZE + proc->pc;
	if (!set_op(arena->memory[proc->pc], &proc->op))
	{
		proc->offset = 1;
		proc->wait = arena->clock + 1;
		return ;
	}
	proc->wait = proc->op.cycle_cost + arena->clock - 1;
	set_instruction(proc, proc->op.op_code);
}
