/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:49:05 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/07 14:50:23 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "GOL.h"

//       012
//    
//    0  ..O
//    1  O.O
//    2  .OO
void	draw_glider(Vector2 position, Color color)
{
	int	x;
	int	y;
	int	offset;

	x = mod((int)position.x, WIDTH);
	y = mod((int)position.y, HEIGHT);
	offset = -1;
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
}

void	put_glider(bool board[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;
	int	offset;

	x = (int)position.x;
	y = (int)position.y;
	offset = -1;
	board[mod(x + 2 + offset + WIDTH, WIDTH)][mod(y + 0 + offset + HEIGHT, HEIGHT)] = true;
	board[mod(x + 2 + offset + WIDTH, WIDTH)][mod(y + 1 + offset + HEIGHT, HEIGHT)] = true;
	board[mod(x + 2 + offset + WIDTH, WIDTH)][mod(y + 2 + offset + HEIGHT, HEIGHT)] = true;
	board[mod(x + 1 + offset + WIDTH, WIDTH)][mod(y + 2 + offset + HEIGHT, HEIGHT)] = true;
	board[mod(x + 0 + offset + WIDTH, WIDTH)][mod(y + 1 + offset + HEIGHT, HEIGHT)] = true;
}
