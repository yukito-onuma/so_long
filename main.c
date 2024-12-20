/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2024/12/20 23:26:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, struct map *struct_map)
{
	if (keycode == XK_Escape)
		exit(0);
	if (keycode == XK_a)
		move_a(struct_map);
	if (keycode == XK_d)
		move_d(struct_map);
	if (keycode == XK_w)
		move_w(struct_map);
	if (keycode == XK_s)
		move_s(struct_map);
	return (0);
}

int	draw_map(struct map *map)
{
	int	x;
	int	y;
	void	*img_1;
	void	*img_E;
	void	*img_P;
	void	*img_C;
	void    *img_0;

	// ここまとめられるだろ！
	img_1 = mlx_xpm_file_to_image(map->mlx, map->texture.img_1, &map->texture.img_width, &map->texture.img_height);
	if (img_1 == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_E = mlx_xpm_file_to_image(map->mlx, map->texture.img_E, &map->texture.img_width, &map->texture.img_height);
	if (img_E == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_P = mlx_xpm_file_to_image(map->mlx, map->texture.img_P, &map->texture.img_width, &map->texture.img_height);
	if (img_P == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_C = mlx_xpm_file_to_image(map->mlx, map->texture.img_C, &map->texture.img_width, &map->texture.img_height);
	if (img_C == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_0 = mlx_xpm_file_to_image(map->mlx, map->texture.img_0, &map->texture.img_width, &map->texture.img_height);
	if (img_0 == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '1')
				mlx_put_image_to_window(map->mlx, map->win, img_1, x * map->texture.img_width , y * map->texture.img_height);
			if (map->map[y][x] == 'E')
				mlx_put_image_to_window(map->mlx, map->win, img_E, x * map->texture.img_width, y * map->texture.img_height);
			if (map->map[y][x] == 'P')
				mlx_put_image_to_window(map->mlx, map->win, img_P, x * map->texture.img_width, y * map->texture.img_height);
			if (map->map[y][x] == 'C')
				mlx_put_image_to_window(map->mlx, map->win, img_C, x * map->texture.img_width, y * map->texture.img_height);
			if (map->map[y][x] == '0')
				mlx_put_image_to_window(map->mlx, map->win, img_0, x * map->texture.img_width, y * map->texture.img_height);
			x++;
		}
		y++;
	}
	mlx_destroy_image(map->mlx, img_1);
	mlx_destroy_image(map->mlx, img_E);
	mlx_destroy_image(map->mlx, img_P);
	mlx_destroy_image(map->mlx, img_C);
	mlx_destroy_image(map->mlx, img_0);

	return (0);
}

int	check_map_inclument(struct map *map_struct)
{
	int is_E;
	int is_P;
	int is_C;
	int width;
	int height;

	is_E = 0;
	is_P = 0;
	is_C = 0;
	width = map_struct->width;
	height = map_struct->height;
	printf("%d\n", __LINE__);
	while (height)
	{
		width = map_struct->width;
		while (width)
		{
			if (map_struct->map[height - 1][width - 1] == 'E')
				is_E++;
			if (map_struct->map[height - 1][width - 1] == 'P')
				is_P++;
			if (map_struct->map[height - 1][width - 1] == 'C')
				is_C++;
			width--;
		}
		height--;
	}
	printf("is_E: %d, is_P: %d, is_C: %d\n", is_E, is_P, is_C);
	if (is_E == 0 || is_P == 0 || is_C == 0)
	{
		fprintf(stderr, "Error: Map is invalid\n");
		map_struct->is_invalid = 1;
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

void	read_map(struct map *map_struct)
{
	map_init(map_struct);
	map_struct->map = (char **)malloc(sizeof(char *) * 5);
	map_struct->map[0] = strdup("11111111"); // 仮置きのstrdup
	map_struct->map[1] = strdup("10000001");
	map_struct->map[2] = strdup("100EP001");
	map_struct->map[3] = strdup("1000C001");
	map_struct->map[4] = strdup("11111111");
	map_struct->height = 5;
	map_struct->width = 8;
	if (check_map_inclument(map_struct) == -1)
		map_struct->is_invalid = 1;
	// if (check_map_structure(map_struct) == -1) // マップの構造が正しいかチェック
	// 	map_struct.is_invalid = 1;
}

struct texture	set_tecture(void)
{
	struct texture	texture;

	texture.img_1 = "image/akamite_dot.xpm";
	texture.img_0 = "image/0.xpm";
	texture.img_E = "image/E.xpm";
	texture.img_P = "image/P.xpm";
	texture.img_C = "image/C.xpm";
	texture.character = "image/character.xpm";
	
	return (texture);
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
	int		img_width;
	int		img_height;
	int		win_width = 800;
	int		win_height = 600;
	struct map	map_struct;
	struct texture	texture;

	map_struct.mlx = mlx_init();
	if (map_struct.mlx == NULL)
	{
		fprintf(stderr, "Error initializing MLX\n");
		return (1);
	}
	map_struct.win = mlx_new_window(map_struct.mlx, win_width, win_height, "Display Image");
	if (map_struct.win == NULL)
	{
		fprintf(stderr, "Error creating window\n");
		return (1);
	}
	printf("%d\n", __LINE__);
	map_struct.texture = set_tecture();
	printf("%d\n", __LINE__);
	read_map(&map_struct); // マップになんの要素を持たせるか検討
	printf("%d\n", __LINE__);
	if (map_struct.is_invalid == 1)
		return (print_error(&map_struct));
	mlx_hook(map_struct.win, KeyPress, KeyPressMask, handle_keypress, &map_struct);
	mlx_loop_hook(map_struct.mlx, draw_map, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}