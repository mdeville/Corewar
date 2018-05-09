/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:13:40 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/09 17:39:50 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** VM related header file
*/

# include <stdlib.h>
# include <unistd.h>
# include <ncurses.h>
# include <op.h>

# include <libft.h>

struct s_option
{
	size_t	dump;
	size_t	cycles;
	t_bool	gfx;
};

/*
** -------------------
*/

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
	t_dlist			*processes;
	t_player		players[MAX_PLAYERS];
	unsigned int	clock;
}					t_arena;

typedef struct		s_player
{
	unsigned int	id;
	t_header		header;
	unsigned int	last_live;
}					t_player;

/*
** --------------------
*/

typedef struct		s_process
{
	unsigned int	pc;
	unsigned int	wait;		/* temps d'attente en cycle avt proch instru */
	unsigned int	registers[REG_NUMBER];
}					t_process;

/*
** @utils.c
*/

void		usage(void);

/*
** @options
*/

t_bool		parse_options(int argc, char *argv[], struct s_option *opts);

#endif
