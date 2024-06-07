/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GOL.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:44:25 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/07 14:58:34 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef GOL_H
# define GOL_H

/* @------------------------------------------------------------------------@ */
/* |                            Include Section                             | */
/* @------------------------------------------------------------------------@ */

# include "raylib.h"
# include "raymath.h"
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

/* @------------------------------------------------------------------------@ */
/* |                            Define Section                              | */
/* @------------------------------------------------------------------------@ */

# define WIDTH 150
# define HEIGHT 80
# define PIXEL_SIZE 8
# define UPDATE_RATE 10
# define FPS 60
# define SCREEN_WIDTH (WIDTH * PIXEL_SIZE)
# define SCREEN_HEIGHT (HEIGHT * PIXEL_SIZE)
# define DEFAULT_FOREGROUND_COLOR RED
# define DEFAULT_BACKGROUND_COLOR BLACK
# define DEFAULT_DRAWING_COLOR GREEN
# define DEFAULT_CURSOR_COLOR YELLOW

/* @------------------------------------------------------------------------@ */
/* |                            Typedef Section                             | */
/* @------------------------------------------------------------------------@ */

typedef struct s_game Game;

/* @------------------------------------------------------------------------@ */
/* |                             Enum Section                               | */
/* @------------------------------------------------------------------------@ */

enum e_state
{
	DEAD,
	ALIVE,
};

enum e_used_keys
{
	G,
	B,
	MAX_USED_KEYS,
};

/* @------------------------------------------------------------------------@ */
/* |                            Struct Section                              | */
/* @------------------------------------------------------------------------@ */

struct s_game
{
	bool	board[WIDTH][HEIGHT];
	int		frameCount;
	bool	isPaused;
	int		speed;
	bool	isKeyUsed[MAX_USED_KEYS];
	int		keyUsedCounter[MAX_USED_KEYS];
	int		keyPatternAmount[MAX_USED_KEYS];
	Color	background_color;
	Color	foreground_color;
	Color	drawing_color;
	Color	cursor_color;
};

/* @------------------------------------------------------------------------@ */
/* |                           Function Section                             | */
/* @------------------------------------------------------------------------@ */

void	draw_glider(Vector2 position, Color color);
void	draw_gospel_gun_glider(Vector2 position, Color color);
void	draw_blinker(Vector2 position, Color color);
void	put_glider(bool board[WIDTH][HEIGHT], Vector2 position);
void	put_gospel_gun_glider(bool board[WIDTH][HEIGHT], Vector2 position);
void	put_blinker(bool board[WIDTH][HEIGHT], Vector2 position);

int		mod(int n1, int n2);

#endif // GOL_H
