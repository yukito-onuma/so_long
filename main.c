/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2025/01/11 18:21:57 by yonuma           ###   ########.fr       */
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
	draw_map(struct_map);
	if (struct_map->count_tea == struct_map->count_teas)
	{
		printf("You win!\n");
		exit(0);
	}
	return (0);
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

void	set_mlx_win(struct map *map_struct)
{
	map_struct->mlx = mlx_init();
	if (map_struct->mlx == NULL)
	{
		fprintf(stderr, "Error\n");
		exit(1);
	}
	map_struct->win = mlx_new_window(map_struct->mlx, 1800, 600, "so_long");
	if (map_struct->win == NULL)
	{
		fprintf(stderr, "Error\n");
		exit(1);
	}
}

int	main(void)
{
	void			*mlx;
	void			*win;
	struct map		map_struct;
	struct texture	texture;

	set_mlx_win(&map_struct);
	map_init(&map_struct);
	map_struct.texture = set_texture();
	read_map(&map_struct);
	if (map_struct.is_invalid == 1)
		return (1); // error書いといて
	draw_map(&map_struct);
	mlx_key_hook(map_struct.win, handle_keypress, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}
