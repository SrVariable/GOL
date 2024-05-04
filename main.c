/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:40:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/05/04 12:31:02 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 50
#define HEIGHT 25
#define PIXEL_SIZE 16
#define UPDATE_RATE 11

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void	initialise_scene(Camera2D *camera)
{
	camera->zoom = 1.0f;
	camera->offset.x = 0;
	camera->offset.y = 0;
	SetTargetFPS(60);
	HideCursor();
}

static int	count_neighbours(bool cell[WIDTH][HEIGHT], Vector2 position)
{
	int	neighbour;
	int	x;
	int	y;

	neighbour = 0;
	x = (int)position.x;
	y = (int)position.y;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			if ((x + i >= 0 && x + i < WIDTH) && (y + j >= 0 && y + j < HEIGHT)
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
			neighbours = count_neighbours(cell, (Vector2){i, j});
			if (neighbours == 3)
				temp[i][j] = true;
			else if (neighbours == 2)
				temp[i][j] = cell[i][j];
			else
				temp[i][j] = false;
		}
	}
	for (int i = 0; i < WIDTH; ++i)
		memcpy(cell[i], temp[i], HEIGHT * sizeof(bool));
}

static void	draw_board(bool cell[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			if (cell[i][j])
				DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE,
								PIXEL_SIZE, PIXEL_SIZE, RED);
}

static void	gol(bool cell[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			if (i % 2 == 0 && j % 2 == 0)
				cell[i][j] = false;
}

static void	put_glider(bool cell[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if ((x < 0 || x + 2 >= WIDTH) && (y < 0 || y + 2 >= HEIGHT))
		return ;
	cell[x + 2][y + 0] = true;
	cell[x + 2][y + 1] = true;
	cell[x + 2][y + 2] = true;
	cell[x + 1][y + 2] = true;
	cell[x + 0][y + 1] = true;
}

static void	draw_glider(Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if ((x < 0 || x + 2 >= WIDTH) && (y < 0 || y + 2 >= HEIGHT))
		return ;
	DrawRectangle((x + 2) * PIXEL_SIZE, (y + 0) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
	DrawRectangle((x + 2) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
	DrawRectangle((x + 2) * PIXEL_SIZE, (y + 2) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
	DrawRectangle((x + 1) * PIXEL_SIZE, (y + 2) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
	DrawRectangle((x + 0) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
}

static void	put_blinker(bool cell[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if ((x < 0 || x + 2 >= WIDTH) && (y < 0 || y + 2 >= HEIGHT))
		return ;
	cell[x + 0][y] = true;
	cell[x + 1][y] = true;
	cell[x + 2][y] = true;
}

static void	draw_blinker(Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if ((x < 0 || x + 2 >= WIDTH) && y < 0)
		return ;
	DrawRectangle((x + 0) * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
	DrawRectangle((x + 1) * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
	DrawRectangle((x + 2) * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, RED);
}

static void	click_cell(bool cell[WIDTH][HEIGHT])
{
	int	x;
	int y;

	x = GetMouseX() / PIXEL_SIZE;
	y = GetMouseY() / PIXEL_SIZE;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	cell[x][y] = !cell[x][y];
}

int	main(void)
{
	Camera2D		camera;
	static bool		cell[WIDTH][HEIGHT];
	static int		frame_count;
	static bool		isPaused = true;
	static int		delay;

	gol(cell);

	InitWindow(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, "GOL");
	initialise_scene(&camera);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);
		draw_board(cell);
		EndMode2D();
		if (isPaused)
			DrawText("Press space to play",
					WIDTH / 3 * PIXEL_SIZE, HEIGHT / 2 * PIXEL_SIZE,
					32, WHITE);
		if (IsKeyDown(KEY_G))
		{
			draw_glider((Vector2){GetMouseX() / PIXEL_SIZE,
									GetMouseY() / PIXEL_SIZE});
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				put_glider(cell, (Vector2){GetMouseX() / PIXEL_SIZE,
											GetMouseY() / PIXEL_SIZE});
		}
		else if (IsKeyDown(KEY_B))
		{
			draw_blinker((Vector2){GetMouseX() / PIXEL_SIZE,
									GetMouseY() / PIXEL_SIZE});
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				put_blinker(cell, (Vector2){GetMouseX() / PIXEL_SIZE,
											GetMouseY() / PIXEL_SIZE});
		}
		else
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				click_cell(cell);
		DrawCircle(GetMouseX(), GetMouseY(), PIXEL_SIZE / 4, YELLOW);
		EndDrawing();
		if (IsKeyPressed(KEY_SPACE))
			isPaused = !isPaused;
		else if (IsKeyDown(KEY_COMMA) && UPDATE_RATE + delay < 20)
			++delay;
		else if (IsKeyDown(KEY_PERIOD) && UPDATE_RATE + delay > 1)
			--delay;
		if (++frame_count % (UPDATE_RATE + delay) == 0 && !isPaused)
		{
			update_board(cell);
			if (frame_count == 10000)
				frame_count = 0;
		}
	}
	CloseWindow();
	return (0);
}
