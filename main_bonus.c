/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:46:56 by marvin            #+#    #+#             */
/*   Updated: 2025/01/11 19:56:24 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    move(int keycode, t_map *struct_map)
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

void    move_bonus(int keycode, t_map *struct_map)
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

int	handle_keypress(int keycode, t_map *struct_map)
{
    static int	tmp = 0;

    if (!struct_map->goal)
        move(keycode, struct_map);
    else
        move_bonus(keycode, struct_map);
    if (tmp != struct_map->count)
    {
        printf("count: %d\n", struct_map->count);
        tmp = struct_map->count;
    }
    draw_map(struct_map);
    if (struct_map->count_tea == struct_map->count_teas)
        struct_map->goal = true;
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

int apply_gravity(t_map *map)
{
    if (map->goal)
    {
        static clock_t last_time = 0;
        clock_t current_time = clock();
        double elapsed_time = ((double)(current_time - last_time)) / CLOCKS_PER_SEC;

        if (elapsed_time < 0.1)
            return 0;

        double g = 9.8;
        last_time = current_time;

        if (map->is_jumping)
        {
            map->jump_time += elapsed_time;
            double V_y = map->jump_velocity - g * map->jump_time;
            int new_y = map->player_y - (int)V_y;
            if (map->map != NULL) {
                if (new_y >= map->height || new_y < 0 || (map->map[new_y] != NULL && map->map[new_y][map->player_x] != '0'))
                {
                    map->is_jumping = false;
                    map->jump_time = 0;
                    return 0;
                }
                if (map->map[map->player_y] != NULL) {
                    map->map[map->player_y][map->player_x] = '0';
                }
                if (map->map[new_y] != NULL) {
                    map->map[new_y][map->player_x] = 'P';
                }
                map->player_y = new_y;
                draw_map(map);
            }
        }
        else
        {
            int new_y = map->player_y + 1;
            if (map->map != NULL) {
                if (new_y < map->height && map->map[new_y] != NULL && map->map[new_y][map->player_x] == '0')
                {
                    if (map->map[map->player_y] != NULL) {
                        map->map[map->player_y][map->player_x] = '0';
                    }
                    map->map[new_y][map->player_x] = 'P';
                    map->player_y = new_y;
                    draw_map(map);
                }
            }
        }
    }
    return 0;
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
	mlx_loop(map_struct.mlx);
	return (0);
}
