/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:57:26 by yonuma            #+#    #+#             */
/*   Updated: 2025/01/11 16:26:45 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void move_a_bonus(t_map *map)
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
                if (x > 0 && (map->map[y][x - 1] == '0'
                    || map->map[y][x - 1] == 'C'))
                {
                    if (map->map[y][x - 1] == 'C')
                        map->count_tea++;
                    map->map[y][x - 1] = 'P';
                    map->map[y][x] = '0';
                    map->count++;
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}

void move_d_bonus(t_map *map)
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
                if (x < map->width - 1 && (map->map[y][x + 1] == '0'
                    || map->map[y][x + 1] == 'C'))
                {
                    if (map->map[y][x + 1] == 'C')
                        map->count_tea++;
                    map->map[y][x + 1] = 'P';
                    map->map[y][x] = '0';
                    map->count++;
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}

void move_w_bonus(t_map *map)
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
                if (y > 0 && (map->map[y - 1][x] == '0'
                    || map->map[y - 1][x] == 'C'))
                {
                    if (map->map[y - 1][x] == 'C')
                        map->count_tea++;
                    map->map[y - 1][x] = 'P';
                    map->map[y][x] = '0';
                    map->count++;
                    return ;
                }
                usleep(1000);
                if (map->map[y - 1][x] == 'E')
                {
                    map->is_E = true;
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}

void move_s_bonus(t_map *map)
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
                if (y < map->height - 1 && (map->map[y + 1][x] == '0'
                    || map->map[y + 1][x] == 'C'))
                {
                    if (map->map[y + 1][x] == 'C')
                        map->count_tea++;
                    map->map[y + 1][x] = 'P';
                    map->map[y][x] = '0';
                    map->count++;
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}
