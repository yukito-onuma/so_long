/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:50:19 by yonuma            #+#    #+#             */
/*   Updated: 2025/01/16 15:55:18 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
