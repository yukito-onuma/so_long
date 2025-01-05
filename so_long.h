/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:49:47 by marvin            #+#    #+#             */
/*   Updated: 2024/12/20 11:49:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "libmlx/mlx.h"

typedef struct texture
{
    void *img_0;
    void *img_window;
    void *img_wall;
    void *img_PC1;
    void *img_PC2;
    void *img_E;
    void *img_Person1;
    void *img_Person2;
    void *img_tea;
    void *character;
    int width;
    int height;
    int img_width;
    int img_height;
} texture;

typedef struct map
{
    char **map;
    void *mlx;
    void *win;
    int width;
    int height;
    int is_invalid;
    int count;
    int count_tea;
    int count_teas;
    bool goal;
    struct texture texture;
} t_map;

// move
void    move_a(struct map *map);
void    move_d(struct map *map);
void    move_w(struct map *map);
void    move_s(struct map *map);

#endif