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

void move_a(struct map *map)
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
                if (x > 0 && map->map[y][x - 1] == '0')
                {
                    map->map[y][x - 1] = 'P';
                    map->map[y][x] = '0';
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}

void move_d(struct map *map)
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
                if (x < map->width - 1 && map->map[y][x + 1] == '0')
                {
                    map->map[y][x + 1] = 'P';
                    map->map[y][x] = '0';
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}

void move_w(struct map *map)
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
                if (y > 0 && map->map[y - 1][x] == '0')
                {
                    map->map[y - 1][x] = 'P';
                    map->map[y][x] = '0';
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}

void move_s(struct map *map)
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
                if (y < map->height - 1 && map->map[y + 1][x] == '0')
                {
                    map->map[y + 1][x] = 'P';
                    map->map[y][x] = '0';
                    return ;
                }
            }
            x++;
        }
        y++;
    }
}