/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:44:43 by marvin            #+#    #+#             */
/*   Updated: 2024/12/20 11:44:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void find_player(t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->map[y][x] == 'P')
            {
                map->player_x = x;
                map->player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}

void move_a(t_map *map)
{
    find_player(map);
    int x = map->player_x;
    int y = map->player_y;

    if (x > 0 && (map->map[y][x - 1] == '0' || map->map[y][x - 1] == 'C'))
    {
        if (map->map[y][x - 1] == 'C')
            map->count_tea++;
        map->map[y][x - 1] = 'P';
        map->map[y][x] = '0';
        map->count++;
        map->player_x--;
    }
}

void move_d(t_map *map)
{
    find_player(map);
    int x = map->player_x;
    int y = map->player_y;

    if (x < map->width - 1 && (map->map[y][x + 1] == '0' || map->map[y][x + 1] == 'C'))
    {
        if (map->map[y][x + 1] == 'C')
            map->count_tea++;
        map->map[y][x + 1] = 'P';
        map->map[y][x] = '0';
        map->count++;
        map->player_x++;
    }
}

void    move_w(t_map *map)
{
    find_player(map);
    int x = map->player_x;
    int y = map->player_y;

    if (y > 0 && (map->map[y - 1][x] == '0' || map->map[y - 1][x] == 'C'))
    {
        if (map->map[y - 1][x] == 'C')
            map->count_tea++;
        map->map[y - 1][x] = 'P';
        map->map[y][x] = '0';
        map->count++;
        map->player_y--;
    }
}

void move_w_bonus(t_map *map)
{
    if (!map->is_jumping) // ジャンプ中でなければジャンプ開始
    {
        map->is_jumping = true;
        map->jump_velocity = 5.0; // ジャンプ初速度（調整可能）
        map->jump_time = 0;
    }
}

void move_s(t_map *map)
{
    find_player(map);
    int x = map->player_x;
    int y = map->player_y;

    if (y < map->height - 1 && (map->map[y + 1][x] == '0' || map->map[y + 1][x] == 'C'))
    {
        if (map->map[y + 1][x] == 'C')
            map->count_tea++;
        map->map[y + 1][x] = 'P';
        map->map[y][x] = '0';
        map->count++;
        map->player_y++;
    }
}
