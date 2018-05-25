/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 09:16:38 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/25 10:03:58 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <commons.h>

static void	exec_processes(t_arena *arena)
{
	t_dlist *walk;

	walk = arena->procs;
	while (walk)
	{
		check_process(arena, walk);
		walk = walk->next;
	}
}

/*
** @desc monothilic part of the arena
**       arena.players should be init
**       before fun call.
** @param options retrieved
** @return nil
*/

t_bool		kernel(struct s_option *options, t_arena *arena)
{
	print_player_headers(arena, 0);
	if (options->trash == TRUE)
		dump_player_exec(arena);
	init_arena(arena, options);
	while (arena->procs)
	{
		exec_processes(arena);
		if (arena->clock && arena->clock % arena->cycle_to_die == 0)
			if (proc_filter(arena) > NBR_LIVE)
				arena->cycle_to_die -= CYCLE_DELTA;
		verbose(arena, 3);
		++arena->clock;
	}
	print_winner(arena, 0);
	return (TRUE);
}

/*
** @desc monothilic part of the graphical arena
**       arena.players should be init
**       before fun call.
** @param options retrieved
** @return nil
*/

t_bool		kernel_gfx(struct s_option *options, t_arena *arena)
{
	t_scene	scene;

	if (options->trash == TRUE)
		dump_player_exec(arena);
	init_arena(arena, options);
	init_curses();
	alloc_window(&scene, arena);
	while (arena->procs)
	{
		dump_cycle_memory(&scene, arena);
		keybindinds_callback(getch(), &scene);
		exec_processes(arena);
		if (arena->clock && arena->clock % arena->cycle_to_die == 0)
			if (proc_filter(arena) > NBR_LIVE)
				arena->cycle_to_die -= CYCLE_DELTA;
		refresh();
		++arena->clock;
		usleep(scene.speed);
	}
	free(scene.memory);
	free(scene.sidebar);
	return (TRUE);
}
