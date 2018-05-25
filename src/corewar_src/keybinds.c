/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:27:54 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/25 10:02:44 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

/*
** @desc keybind callback
** @return nil
*/

void	keybindinds_callback(char input,
					t_scene *scene)
{
	char	c;

	if (input == 0x71)
		exit(EXIT_SUCCESS);
	else if (scene->pause || input == 0x20)
	{
		scene->pause = FALSE;
		while (((c = getch()) != 0x20))
			if (c == 0x71)
				exit(EXIT_SUCCESS);
	}
	else if (input == 0x3c)		/* Reduce Speed */
	{
		scene->speed += STEP_SPEED;
		if (scene->speed > MIN_SPEED)
			scene->speed = MIN_SPEED;
	}
	else if (input == 0x3e)		/* Increase Speed */
	{
		scene->speed -= STEP_SPEED;
		if (scene->speed < MAX_SPEED)
			scene->speed = MAX_SPEED;
	}
}
