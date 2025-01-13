/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2025/01/13 21:21:29 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move(int keycode, t_map *struct_map)
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
}

void	move_bonus(int keycode, t_map *struct_map)
{
	if (keycode == XK_Escape)
		exit(0);
	if (keycode == XK_a)
		move_a(struct_map);
	if (keycode == XK_d)
		move_d(struct_map);
	if (keycode == XK_w)
		move_w_bonus(struct_map);
	if (keycode == XK_s)
		move_s_bonus(struct_map);
	if (keycode == XK_space)
		set_obstacle(struct_map);
}

void	set_ememy(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '0')
			{
				map->map[y][x] = 'N';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	handle_keypress(int keycode, t_map *struct_map)
{
	if (!struct_map->goal2)
		move(keycode, struct_map);
	else
	{
		if (struct_map->is_falling)
			return (0);
		move_bonus(keycode, struct_map);
	}
	draw_map(struct_map);
	if (struct_map->count_tea == struct_map->count_teas)
	{
		struct_map->goal1 = true;
		set_ememy(struct_map);
		struct_map->count_tea = 0;
		draw_map(struct_map);
	}
	return (0);
}

void	read_map(struct map *map_struct)
{
	map_init(map_struct);
	map_struct->map = (char **)malloc(sizeof(char *) * 9);
	map_struct->map[0] = strdup("111111111111111111111111111"); // 仮置きのstrdup
	map_struct->map[1] = strdup("111111111111111111111110001");
	map_struct->map[2] = strdup("1P00000000C0000000000010001");
	map_struct->map[3] = strdup("100111111111111111110010001");
	map_struct->map[4] = strdup("100000000000000000000C00001");
	map_struct->map[5] = strdup("100111111111111111110000001");
	map_struct->map[6] = strdup("10C000000000000000000C00001");
	map_struct->map[7] = strdup("100111111111111111110010E01");
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

void	search_player(t_map *map, int *x, int *y)
{
	*y = 0;
	while (*y < map->height)
	{
		*x = 0;
		while (*x < map->width)
		{
			if (map->map[*y][*x] == 'P')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

int	apply_gravity(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	search_player(map, &x, &y);
	if (map->goal1)
	{
		usleep(50000);
		if (map->map[y + 1][x] == '1' || map->map[y + 1][x] == 'O'
			|| map->map[y + 1][x] == 'E')
		{
			map->is_falling = false;
			return (0);
		}
		map->is_falling = true;
		if (map->map[y][x] == 'P' && map->map[y + 1][x] == '0')
		{
			map->map[y + 1][x] = 'P';
			map->map[y][x] = '0';
		}
	}
	draw_map(map);
	return (0);
}

int	enemy(t_map *map)
{
	int	x;
	int	y;
	int	ex;
	int	ey;
	static int	count = 0;

	count ++;
	if (map->goal1 && count == 1)
	{
		printf("count: %d\n", count);
		search_player(map, &x, &y);
		ey = 0;
		while (ey < map->height)
		{
			ex = 0;
			while (ex < map->width)
			{
				if (map->map[ey][ex] == 'N')
				{
					if (ex < x && map->map[ey][ex + 1] == '0')
					{
						map->map[ey][ex] = '0';
						map->map[ey][ex + 1] = 'N';
						break;
					}
					else if (ex > x && map->map[ey][ex - 1] == '0')
					{
						map->map[ey][ex] = '0';
						map->map[ey][ex - 1] = 'N';
						break;
					}
					else if (ey < y && map->map[ey + 1][ex] == '0')
					{
						map->map[ey][ex] = '0';
						map->map[ey + 1][ex] = 'N';
						break;
					}
					else if (ey > y && map->map[ey - 1][ex] == '0')
					{
						map->map[ey][ex] = '0';
						map->map[ey - 1][ex] = 'N';
						break;
					}
				}
				ex++;
			}
			ey++;
		}
		draw_map(map);
	}
	if (count == 50000)
		count = 0;
	return (0);
}

int	main(void)
{
	void			*mlx;
	void			*win;
	struct map		map_struct;
	struct texture	texture;

	set_mlx_win(&map_struct);
	map_init(&map_struct);
	read_map(&map_struct);
	if (map_struct.is_invalid == 1)
		return (1); // error書いといて
	draw_map(&map_struct);
	mlx_key_hook(map_struct.win, handle_keypress, &map_struct);
	mlx_loop_hook(map_struct.mlx, apply_gravity, &map_struct);
	mlx_loop_hook(map_struct.mlx, enemy, &map_struct);
	mlx_loop(map_struct.mlx);
	return (0);
}
