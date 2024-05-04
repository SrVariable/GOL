/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:40:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/05/04 10:28:22 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 50
#define HEIGHT 25
#define PIXEL_SIZE 16
#define RATIO (WIDTH / HEIGHT)
#define UPDATE_RATE 11

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
	camera->zoom = 1.0f;
	camera->offset.x = 0;
	camera->offset.y = 0;
	SetTargetFPS(60);
	HideCursor();
}

static int	count_neighbours(bool cell[WIDTH][HEIGHT], Vector2 position)
{
	int	neighbour;

	neighbour = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			if (((int)position.x + i >= 0 && (int)position.x + i < WIDTH)
				&& ((int)position.y + j >= 0 && (int)position.y + j < HEIGHT)
				&& cell[(int)position.x + i][(int)position.y + j])
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
			if (!cell[i][j])
				DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE,
								PIXEL_SIZE, PIXEL_SIZE, BLACK);
			else
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
	if (((int)position.x < 0 || (int)position.x + 2 >= WIDTH)
			&& ((int)position.y < 0 || (int)position.y + 2 >= HEIGHT))
		return ;
	cell[2 + (int)position.x][0 + (int)position.y] = true;
	cell[2 + (int)position.x][1 + (int)position.y] = true;
	cell[2 + (int)position.x][2 + (int)position.y] = true;
	cell[1 + (int)position.x][2 + (int)position.y] = true;
	cell[0 + (int)position.x][1 + (int)position.y] = true;
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
	Vector2 		previousMousePosition;
	Camera2D		camera;
	static bool		cell[WIDTH][HEIGHT];
	static float	size;
	static int		frame_count;
	static bool		isPaused = true;
	static int		delay;

	gol(cell);

	put_glider(cell, (Vector2){0, 0});
	put_glider(cell, (Vector2){8, 0});
	put_glider(cell, (Vector2){16, 0});

	InitWindow(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, "GOL");
	initialise_scene(&camera);
	previousMousePosition = GetMousePosition();
	while (!WindowShouldClose())
	{
		move_camera_with_mouse_cursor(&camera, &previousMousePosition);
		BeginDrawing();
		ClearBackground(GetColor(0x106969ff));
		BeginMode2D(camera);
		draw_board(cell);
		EndMode2D();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			click_cell(cell);
		DrawCircle(GetMouseX() - PIXEL_SIZE / 4, GetMouseY() - PIXEL_SIZE / 4,
					PIXEL_SIZE / 4 + size, WHITE);
		if (isPaused)
			DrawText("Press space to play",
					GetScreenWidth() / 6, GetScreenHeight() / 2.5, RATIO * PIXEL_SIZE, WHITE);
		EndDrawing();
		if (IsKeyPressed(KEY_SPACE))
			isPaused = !isPaused;
		else if (IsKeyDown(KEY_COMMA))
			++delay;
		else if (IsKeyDown(KEY_PERIOD) && UPDATE_RATE + delay > 1)
			--delay;
		if (++frame_count % (int)(UPDATE_RATE + delay) == 0 && !isPaused)
		{
			update_board(cell);
			if (frame_count == 10000)
				frame_count = 0;
		}
	}
	CloseWindow();
	return (0);
}
