/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 00:10:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string.h>
#include "libmlx/mlx.h"
#include "so_long.h"

int	close(int keycode, void *param)
{
	(void)param;
	if (keycode == XK_Escape)
		exit(0);
	return (0);
}

void	draw_map(struct map *map, void *mlx, void *win, void *img, int img_width, int img_height)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '1')
				mlx_put_image_to_window(mlx, win, img, x * img_width, y * img_height);
			x++;
		}
		y++;
	}
}

int	check_map_inclument(struct map map_struct)
{
	int is_E;
	int is_P;
	int is_C;
	int width;

	is_E = 0;
	is_P = 0;
	is_C = 0;
	width = map_struct.width;
	printf("map_struct.height: %d, map_struct.width: %d\n", map_struct.height, map_struct.width);
	while (map_struct.height)
	{
		map_struct.width = width;
		while (map_struct.width)
		{
			if (map_struct.map[map_struct.height - 1][map_struct.width - 1] == 'E')
				is_E++;
			if (map_struct.map[map_struct.height - 1][map_struct.width - 1] == 'P')
				is_P++;
			if (map_struct.map[map_struct.height - 1][map_struct.width - 1] == 'C')
				is_C++;
			map_struct.width--;
		}
		map_struct.height--;
	}
	printf("is_E: %d, is_P: %d, is_C: %d\n", is_E, is_P, is_C);
	if (is_E == 0 || is_P == 0 || is_C == 0)
	{
		fprintf(stderr, "Error: Map is invalid\n");
		map_struct.is_invalid = 1;
		return (-1);
	}
	return (0);
}

void	map_init(struct map *map_struct)
{
	map_struct->map = NULL;
	map_struct->width = 0;
	map_struct->height = 0;
	map_struct->is_invalid = 0;
}

struct map read_map(void)
{
	struct map map_struct;

	map_init(&map_struct);
	map_struct.map = (char **)malloc(sizeof(char *) * 5);
	map_struct.map[0] = strdup("11111111"); // 仮置きのstrdup
	map_struct.map[1] = strdup("10000001");
	map_struct.map[2] = strdup("100EP001");
	map_struct.map[3] = strdup("1000C001");
	map_struct.map[4] = strdup("11111111");
	map_struct.height = 5;
	map_struct.width = 8;
	if (check_map_inclument(map_struct) == -1)
		map_struct.is_invalid = 1;
	// if (check_map_structure(map_struct) == -1) // マップの構造が正しいかチェック
	// 	map_struct.is_invalid = 1;
	return (map_struct);
}

int	print_error(struct map *map_struct)
{
	while (map_struct->height)
	{
		free(map_struct->map[map_struct->height - 1]);
		map_struct->height--;
	}
	free(map_struct->map);
	return (1);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*relative_path = "image/akamite_dot.xpm";
	int		img_width;
	int		img_height;
	int		win_width = 800;
	int		win_height = 600;
	struct map	map_struct;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		fprintf(stderr, "Error initializing MLX\n");
		return (1);
	}
	win = mlx_new_window(mlx, win_width, win_height, "Display Image");
	if (win == NULL)
	{
		fprintf(stderr, "Error creating window\n");
		return (1);
	}
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	if (img == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		return (1);
	}
	mlx_hook(win, KeyPress, KeyPressMask, close, NULL);
	map_struct = read_map(); // マップになんの要素を持たせるか検討
	if (map_struct.is_invalid == 1)
		return (print_error(&map_struct));
	draw_map(&map_struct, mlx, win, img, img_width, img_height); // 画像を敷き詰める

	mlx_loop(mlx);
	return (0);
}