/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2025/01/05 20:49:08 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_map *struct_map)
{
	static int	tmp = 0;

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
	if (tmp != struct_map->count)
		printf("count: %d\n", struct_map->count);
	tmp = struct_map->count;
	if (struct_map->count_tea == struct_map->count_teas) // 歩数INT_MAX問題
	{
		struct_map->goal = true;
		printf("You win!\n"); // リーク直してね
		// exit(0);
	}
	return (0);
}

// アイディアだけあるテクスチャの張替え
// struct texture	set_new_tecture(void) // 新しいテクスチャをセットする
// {
// 	struct texture	texture;

// 	texture.img_window = "image/window.xpm";
// 	texture.img_wall = "image/wall.xpm";
// 	texture.img_PC1 = "image/PC1.xpm";
// 	texture.img_PC2 = "image/PC2.xpm";
// 	texture.img_0 = "image/collidor.xpm";
// 	texture.img_E = "image/akamite_dot.xpm";
// 	texture.img_Person1 = "image/person1.xpm";
// 	texture.img_Person2 = "image/person2.xpm";
// 	texture.img_tea = "image/tea.xpm";
// 	texture.character = "image/character.xpm";

// 	return (texture);
// }

int	draw_map(t_map *map)
{
	int	x;
	int	y;
	void	*img_window;
	void	*img_wall;
	void	*img_PC1;
	void	*img_PC2;
	void	*img_E;
	void	*img_Person1;
	void	*img_Person2;
	void	*img_tea;
	void    *img_0;
	bool    next_PC1 = true;
	static  bool    person = true;

	// もしテクスチャを張り替えたいならここで	
	// if (map->goal)
	// 	map->texture = set_new_tecture();
	// ここまとめられるだろ！
	img_window = mlx_xpm_file_to_image(map->mlx, map->texture.img_window, &map->texture.img_width, &map->texture.img_height);
	if (img_window == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_wall = mlx_xpm_file_to_image(map->mlx, map->texture.img_wall, &map->texture.img_width, &map->texture.img_height);
	if (img_wall == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_PC1 = mlx_xpm_file_to_image(map->mlx, map->texture.img_PC1, &map->texture.img_width, &map->texture.img_height);
	if (img_PC1 == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_PC2 = mlx_xpm_file_to_image(map->mlx, map->texture.img_PC2, &map->texture.img_width, &map->texture.img_height);
	if (img_PC2 == NULL)
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
	img_Person1 = mlx_xpm_file_to_image(map->mlx, map->texture.img_Person1, &map->texture.img_width, &map->texture.img_height);
	if (img_Person1 == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_Person2 = mlx_xpm_file_to_image(map->mlx, map->texture.img_Person2, &map->texture.img_width, &map->texture.img_height);
	if (img_Person2 == NULL)
	{
		fprintf(stderr, "Error loading image\n");
		exit(1);
	}
	img_tea = mlx_xpm_file_to_image(map->mlx, map->texture.img_tea, &map->texture.img_width, &map->texture.img_height);
	if (img_tea == NULL)
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
			{
				if (x == 0 || x == map->width - 1)
					mlx_put_image_to_window(map->mlx, map->win, img_wall, x * map->texture.img_width , y * map->texture.img_height);
				else if (y == 0)
					mlx_put_image_to_window(map->mlx, map->win, img_window, x * map->texture.img_width , y * map->texture.img_height);
				else if (y == map->height- 1)
					mlx_put_image_to_window(map->mlx, map->win, img_PC2, x * map->texture.img_width , y * map->texture.img_height);
				else if (y == 1)
					mlx_put_image_to_window(map->mlx, map->win, img_PC1, x * map->texture.img_width , y * map->texture.img_height);
				else
				{
					if (next_PC1)
					{
						mlx_put_image_to_window(map->mlx, map->win, img_PC1, x * map->texture.img_width, y * map->texture.img_height);
						next_PC1 = false;
					}
					else
					{
						mlx_put_image_to_window(map->mlx, map->win, img_PC2, x * map->texture.img_width, y * map->texture.img_height);
						next_PC1 = true;
					}
				}
			}
			if (map->map[y][x] == 'E')
				mlx_put_image_to_window(map->mlx, map->win, img_E, x * map->texture.img_width, y * map->texture.img_height);
			if (map->map[y][x] == 'P')
			{
				if (person)
				{
					mlx_put_image_to_window(map->mlx, map->win, img_Person1, x * map->texture.img_width, y * map->texture.img_height);
					person = false;
				}
				else
				{
					mlx_put_image_to_window(map->mlx, map->win, img_Person2, x * map->texture.img_width, y * map->texture.img_height);
					person = true;
				}
			}
			if (map->map[y][x] == 'C')
				mlx_put_image_to_window(map->mlx, map->win, img_tea, x * map->texture.img_width, y * map->texture.img_height);
			if (map->map[y][x] == '0')
				mlx_put_image_to_window(map->mlx, map->win, img_0, x * map->texture.img_width, y * map->texture.img_height);
			x++;
		}
		y++;
	}
	mlx_destroy_image(map->mlx, img_window);
	mlx_destroy_image(map->mlx, img_wall);
	mlx_destroy_image(map->mlx, img_PC1);
	mlx_destroy_image(map->mlx, img_PC2);
	mlx_destroy_image(map->mlx, img_E);
	mlx_destroy_image(map->mlx, img_Person1);
	mlx_destroy_image(map->mlx, img_Person2);
	mlx_destroy_image(map->mlx, img_tea);
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
	if (is_E == 0 || is_P == 0 || is_C == 0)
	{
		fprintf(stderr, "Error: Map is invalid\n");
		map_struct->is_invalid = 1;
		return (-1);
	}
	map_struct->count_teas = is_C;
	return (0);
}

void	map_init(struct map *map_struct)
{
	map_struct->map = NULL;
	map_struct->width = 0;
	map_struct->height = 0;
	map_struct->is_invalid = 0;
	map_struct->count = 0;
	map_struct->count_tea = 0;
	map_struct->count_teas = 0;
	map_struct->goal = false;
}

void	read_map(struct map *map_struct)
{
	map_init(map_struct);
	map_struct->map = (char **)malloc(sizeof(char *) * 9);
	map_struct->map[0] = strdup("111111111111111111111111111"); // 仮置きのstrdup
	map_struct->map[1] = strdup("111111111111111111111110001");
	map_struct->map[2] = strdup("1P00000000C0000000000010E01");
	map_struct->map[3] = strdup("100111111111111111110010001");
	map_struct->map[4] = strdup("100000000000000000000C00001");
	map_struct->map[5] = strdup("100111111111111111110000001");
	map_struct->map[6] = strdup("10C000000000000000000C00001");
	map_struct->map[7] = strdup("100111111111111111110010001");
	map_struct->map[8] = strdup("100000000000000000000010001");
	map_struct->map[9] = strdup("111111111111111111111111111");
	map_struct->height = 10;
	map_struct->width = 27;
	if (check_map_inclument(map_struct) == -1)
		map_struct->is_invalid = 1;
	// if (check_map_structure(map_struct) == -1) // マップの構造が正しいかチェック
	// 	map_struct.is_invalid = 1;
}

struct texture	set_tecture(void)
{
	struct texture	texture;

	texture.img_window = "image/window.xpm";
	texture.img_wall = "image/wall.xpm";
	texture.img_PC1 = "image/PC1.xpm";
	texture.img_PC2 = "image/PC2.xpm";
	texture.img_0 = "image/collidor.xpm";
	texture.img_E = "image/kaidan.xpm";
	texture.img_Person1 = "image/person1.xpm";
	texture.img_Person2 = "image/person2.xpm";
	texture.img_tea = "image/tea.xpm";
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
	int		win_width = 1800;
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
	map_struct.texture = set_tecture();
	read_map(&map_struct);
	if (map_struct.is_invalid == 1)
		return (print_error(&map_struct));
	mlx_hook(map_struct.win, KeyPress, KeyPressMask, handle_keypress, &map_struct);
	mlx_loop_hook(map_struct.mlx, draw_map, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}
