/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2024/11/17 19:37:41 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "libmlx/mlx.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


int event_handler(int key, void *mlx)
{
	(void)mlx;
	if (key == XK_Escape)
		exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!\n");
	return (0);
}

int	main(void)
{
	t_vars	vars;
	int i = 0;
	char	map[2] = {1,0};
	
	while (i < 2)
	{
		i++;
		if (map[i] == 1)
			
		else
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, event_handler, vars.mlx);
	mlx_loop(vars.mlx);
}

