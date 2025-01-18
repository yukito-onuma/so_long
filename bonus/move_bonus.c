/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:57:26 by yonuma            #+#    #+#             */
/*   Updated: 2025/01/18 13:34:49 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	move_a_bonus(t_map *map)
{
	int	x;
	int	y;

	if (map->is_jumping)
		return ;
	search_player(map, &x, &y);
	if (x > 0 && (map->map[y][x - 1] == '0' || map->map[y][x - 1] == 'C'))
	{
		if (map->map[y][x - 1] == 'C')
			map->count_tea++;
		map->map[y][x - 1] = 'P';
		map->map[y][x] = '0';
		map->count++;
	}
}

void	move_d_bonus(t_map *map)
{
	int	x;
	int	y;

	if (map->is_jumping)
		return ;
	search_player(map, &x, &y);
	if (x < map->width - 1 && (map->map[y][x + 1] == '0' || map->map[y][x + 1] == 'C'))
	{
		if (map->map[y][x + 1] == 'C')
			map->count_tea++;
		map->map[y][x + 1] = 'P';
		map->map[y][x] = '0';
		map->count++;
	}
}

void	move_w_0(t_map *map, int *x, int *y, int *jump)
{
	map->map[*y - 1][*x] = 'P';
	map->map[*y][*x] = '0';
	*y = *y - 1;
	*jump = *jump - 1;
}

void	move_w_O(t_map *map, int *x, int *y, int *jump)
{
	if (map->map[*y - 2][*x] == '1')
	{
		*jump = 0;
		return ;
	}
	else
	{
		map->map[*y - 2][*x] = 'P';
		map->map[*y][*x] = '0';
		*y = *y - 2;
		*jump = *jump - 2;
	}
}

void	move_w_bonus(t_map *map)
{
	int	x;
	int	y;
	int	jump;

	if (map->is_jumping)
		return ;
	jump = 3;
	map->is_jumping = true;
	search_player(map, &x, &y);
	while (jump > 0)
	{
		if (y > 0 && (map->map[y - 1][x] == '0' || map->map[y - 1][x] == 'O'))
		{
			if (map->map[y - 1][x] == 'O')
				move_w_O(map, &x, &y, &jump);
			else
				move_w_0(map, &x, &y, &jump);
		}
		else
		{
			map->is_jumping = false;
			return ;
		}
	}
	map->is_jumping = false;
}

void	move_s_bonus(t_map *map)
{
	int	x;
	int	y;

	if (map->is_jumping)
		return ;
	search_player(map, &x, &y);
	if (map->map[y + 1][x] == 'O')
	{
		map->map[y + 2][x] = 'P';
		map->map[y][x] = '0';
	}
}

void	set_obstacle(t_map *map)
{
	int x;
	int y;

	search_player(map, &x, &y);
	if (map->map[y][x] == 'P')
	{
		if (map->map[y - 1][x] == '0')
		{
			map->map[y - 1][x] = 'O';
			map->map[y][x] = 'P';
		}
	}
}
