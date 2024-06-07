/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gospel_gun_glider.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:52:24 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/07 14:53:42 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "GOL.h"

//       0         1         2         3
//       012345678901234567890123456789012345
//    
//    0  ........................O...........
//    1  ......................O.O...........
//    2  ............OO......OO............OO
//    3  ...........O...O....OO............OO
//    4  OO........O.....O...OO..............
//    5  OO........O...O.OO....O.O...........
//    6  ..........O.....O.......O...........
//    7  ...........O...O....................
//    8  ............OO......................
void	draw_gospel_gun_glider(Vector2 position, Color color)
{
	int	x;
	int	y;
	int	offset;

	x = mod((int)position.x, WIDTH);
	y = mod((int)position.y, HEIGHT);
	offset = -18;

	// 0
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);

	// 1
	DrawRectangle(mod(x + 10 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 10 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 10 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 11 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 12 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 4 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 13 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 4 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 15 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 16 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 16 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 17 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 14 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 16 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 15 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 13 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 12 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 11 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);

	// 2
	DrawRectangle(mod(x + 20 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 20 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 20 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 21 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 21 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 21 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 22 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 22 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 4 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);

	// 3
	DrawRectangle(mod(x + 34 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 34 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 35 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 35 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
}

void	put_gospel_gun_glider(bool board[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;
	int	offset;

	x = (int)position.x;
	y = (int)position.y;
	offset = -18;

	// 0
	board[mod(x + 0 + offset + WIDTH, WIDTH)][mod(y + 0 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 0 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 1 + offset + WIDTH, WIDTH)][mod(y + 0 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 1 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;

	// 1
	board[mod(x + 10 + offset + WIDTH, WIDTH)][mod(y + 0 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 10 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 10 + offset + WIDTH, WIDTH)][mod(y + 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 11 + offset + WIDTH, WIDTH)][mod(y + 3 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 12 + offset + WIDTH, WIDTH)][mod(y + 4 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 13 + offset + WIDTH, WIDTH)][mod(y + 4 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 15 + offset + WIDTH, WIDTH)][mod(y + 3 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 16 + offset + WIDTH, WIDTH)][mod(y + 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 16 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 17 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 14 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 16 + offset + WIDTH, WIDTH)][mod(y + 0 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 15 + offset + WIDTH, WIDTH)][mod(y - 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 13 + offset + WIDTH, WIDTH)][mod(y - 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 12 + offset + WIDTH, WIDTH)][mod(y - 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 11 + offset + WIDTH, WIDTH)][mod(y - 1 + HEIGHT, HEIGHT)] = true;

	// 2
	board[mod(x + 20 + offset + WIDTH, WIDTH)][mod(y - 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 20 + offset + WIDTH, WIDTH)][mod(y - 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 20 + offset + WIDTH, WIDTH)][mod(y - 0 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 21 + offset + WIDTH, WIDTH)][mod(y - 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 21 + offset + WIDTH, WIDTH)][mod(y - 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 21 + offset + WIDTH, WIDTH)][mod(y - 0 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 22 + offset + WIDTH, WIDTH)][mod(y - 3 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 22 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 24 + offset + WIDTH, WIDTH)][mod(y - 3 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 24 + offset + WIDTH, WIDTH)][mod(y + 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 24 + offset + WIDTH, WIDTH)][mod(y - 4 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 24 + offset + WIDTH, WIDTH)][mod(y + 2 + HEIGHT, HEIGHT)] = true;

	// 3
	board[mod(x + 34 + offset + WIDTH, WIDTH)][mod(y - 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 34 + offset + WIDTH, WIDTH)][mod(y - 2 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 35 + offset + WIDTH, WIDTH)][mod(y - 1 + HEIGHT, HEIGHT)] = true;
	board[mod(x + 35 + offset + WIDTH, WIDTH)][mod(y - 2 + HEIGHT, HEIGHT)] = true;
}
