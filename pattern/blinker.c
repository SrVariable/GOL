/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blinker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:54:30 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/07 14:54:36 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "GOL.h"

//       012
//    
//    0  OOO
void	draw_blinker(Vector2 position, Color color)
{
	int	x;
	int	y;
	int	offset;

	x = (int)position.x;
	y = (int)position.y;
	offset = -1;
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
}

void	put_blinker(bool board[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;
	int	offset;

	x = (int)position.x;
	y = (int)position.y;
	offset = -1;
	board[mod(x + 0 + offset + WIDTH, WIDTH)][mod(y + HEIGHT, HEIGHT)] = true;
	board[mod(x + 1 + offset + WIDTH, WIDTH)][mod(y + HEIGHT, HEIGHT)] = true;
	board[mod(x + 2 + offset + WIDTH, WIDTH)][mod(y + HEIGHT, HEIGHT)] = true;
}
