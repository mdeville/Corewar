/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 15:20:10 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/15 11:48:27 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <libft.h>
#include <colors.h>
#include <commons.h>

/*
** @desc print usage and exit;
** @return Nil (exit)
*/

void		usage(void)
{
	ft_printf("Usage: ./corewar [-d nbr_cycles] ");
	ft_printf("[[-n number] champion1.cor] ...\n");
	exit(EXIT_FAILURE);
}

/*
** @desc dump memory to stdout
** @return nil
*/

void		dump_memory(const unsigned char *memory,
					size_t i)
{
	ft_printf("Dumping memory of size: %d\n", MEM_SIZE);
	while (i < MEM_SIZE)
	{
		if (memory[i] == 0xff)
			ft_putstr(BLACK);
		else if (memory[i] == 0x0)
			ft_putstr(GREEN);
		else
			ft_putstr(BOLDGREEN);
		if ((i % 40) == 0)
			ft_putchar('\n');
		ft_printf("%.2x ", memory[i]);
		i++;
	}
	ft_putstr(RESET);
}

/*
** @desc Dump player exec to stdout
** @return nil
*/

void		dump_player_exec(t_arena *arena)
{
	size_t	p;
	size_t	i;

	p = 0;
	while (p < arena->np)
	{
		i = 0;
		swap_endian(&arena->players[p].header.prog_size,
					sizeof(arena->players[p].header.prog_size));
		ft_printf("\nSize of player[%zu]: %u\n", p,
			arena->players[p].header.prog_size);
		while (i < arena->players[p].header.prog_size)
		{
			if (arena->players[p].exec[i] != 0x0)
				ft_putstr(BOLDRED);
			else
				ft_putstr(BLACK);
			if ((i % 15) == 0)
				ft_putchar('\n');
			ft_printf("\\x%.2x ", arena->players[p].exec[i]);
			i++;
		}
		ft_printf("\n%s", RESET);
		p++;
	}
}
