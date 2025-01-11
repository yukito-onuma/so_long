/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:42:36 by yonuma            #+#    #+#             */
/*   Updated: 2025/01/11 19:55:23 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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

	// ここまとめられるだろ！
	if (!map->goal)
		map->texture = set_texture();
	else
		map->texture = set_new_texture();
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
