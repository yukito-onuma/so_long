/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2024/11/14 19:06:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "libmlx/mlx.h"

int event_handler(int key, void *mlx)
{
	(void)mlx;
	if (key == XK_Escape)
		exit(0);
	printf("called\n");
	return (0);
}

int main(void)
{
 void *mlx;
 void *mlx_win;

 mlx = mlx_init();
 mlx_win = mlx_new_window(mlx, 300, 300, "Hello World");
 mlx_hook(mlx_win, KeyPress, KeyPressMask, event_handler, mlx);
 mlx_loop(mlx);
}

