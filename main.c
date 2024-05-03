/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:40:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/05/03 21:42:53 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 40
#define HEIGHT 20
#define PIXEL_SIZE 16
#define UPDATE_RATE 300

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void	move_camera_with_mouse_cursor(Camera2D *camera,
											Vector2 *previousMousePosition)
{
	Vector2 currentMousePosition;
	Vector2 delta;

	currentMousePosition = GetMousePosition();
	delta = Vector2Subtract(*previousMousePosition, currentMousePosition);
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		camera->target = GetScreenToWorld2D(Vector2Add(camera->offset, delta),
											*camera);
	*previousMousePosition = currentMousePosition;
}

static void	initialise_scene(Camera2D *camera)
{
	camera->zoom = 1.5f;
	camera->offset.x = 1.0f;
	camera->offset.y = 1.0f;
	HideCursor();
}

static int	count_neighbours(bool cell[WIDTH][HEIGHT], int x, int y)
{
	int	neighbour;

	neighbour = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			if ((x + i >= 0 && x + i < WIDTH)
				&& (y + j >= 0 && y + j < HEIGHT)
				&& cell[x + i][y + j])
				++neighbour;
		}
	}
	return (neighbour);
}

static void	update_board(bool cell[WIDTH][HEIGHT])
{
	static bool temp[WIDTH][HEIGHT];
	int	neighbours;

	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			neighbours = count_neighbours(cell, i, j);
			if (neighbours == 3)
				temp[i][j] = true;
			else if (neighbours != 2 && neighbours != 3)
				temp[i][j] = false;
		}
	}
	for (int i = 0; i < WIDTH; ++i)
		memcpy(cell[i], temp[i], HEIGHT * sizeof(bool));
}

static void	gol(bool cell[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			if (i % 2 == 0 && j % 2 == 0)
				cell[i][j] = false;
}

int	main(void)
{
	Vector2 		previousMousePosition;
	Camera2D		camera;
	static bool		cell[WIDTH][HEIGHT];
	static float	size;
	static int		delay = 1;

	gol(cell);
	cell[5][10] = true;
	cell[6][10] = true;
	cell[6][11] = true;
	cell[7][10] = true;
	cell[5 + 10][10] = true;
	cell[6 + 10][10] = true;
	cell[6 + 10][11] = true;
	cell[7 + 10][10] = true;
	cell[5 + 20][10] = true;
	cell[6 + 20][10] = true;
	cell[6 + 20][11] = true;
	cell[7 + 20][10] = true;
	InitWindow(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, "GOL");
	initialise_scene(&camera);
	previousMousePosition = GetMousePosition();
	while (!WindowShouldClose())
	{
		move_camera_with_mouse_cursor(&camera, &previousMousePosition);
		BeginDrawing();
		ClearBackground(GetColor(0x106969ff));
		BeginMode2D(camera);
		for (int i = 1; i < WIDTH; ++i)
			for (int j = 1; j < HEIGHT; ++j)
				if (!cell[i][j])
					DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, BLACK);
				else
					DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
		EndMode2D();
		DrawCircle(GetMouseX() - PIXEL_SIZE / 4, GetMouseY() - PIXEL_SIZE / 4, PIXEL_SIZE / 4 + size, WHITE);
		EndDrawing();
		if (delay++ % UPDATE_RATE == 0)
			update_board(cell);
		if (delay == 10000)
			delay = 0;
	}
	CloseWindow();
	return (0);
}
