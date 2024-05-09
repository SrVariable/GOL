/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:40:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/05/09 06:34:51 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 75		// Width of the board
#define HEIGHT 40		// Height of the board
#define PIXEL_SIZE 16 	// Size of each pixel
#define UPDATE_RATE 11	// Update rate of the board

// Note: These colors can be replaced using the function GetColor()
// Example color yellow (RGBA Hex): GetColor(0xFFFF00FF)
#define FOREGROUND_COLOR RED	// GOL's foreground color
#define BACKGROUND_COLOR BLACK	// GOL's background color
#define CURSOR_COLOR YELLOW		// GOL's cursor color

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

static int	count_neighbours(bool board[WIDTH][HEIGHT], Vector2 position)
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
				&& board[x + i][y + j])
				++neighbour;
		}
	}
	return (neighbour);
}

static void	draw_board(bool board[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			if (board[i][j])
				DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE,
								PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

static void	clear_board(bool board[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; ++i)
		memset(board[i], false, HEIGHT);
}

static void	update_board(bool board[WIDTH][HEIGHT])
{
	static bool temp[WIDTH][HEIGHT];
	int	neighbours;

	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			neighbours = count_neighbours(board, (Vector2){i, j});
			if (neighbours == 3)
				temp[i][j] = true;
			else if (neighbours == 2)
				temp[i][j] = board[i][j];
			else
				temp[i][j] = false;
		}
	}
	for (int i = 0; i < WIDTH; ++i)
		memcpy(board[i], temp[i], HEIGHT * sizeof(bool));
}

static void	click_on_the_board(bool board[WIDTH][HEIGHT])
{
	int	x;
	int	y;

	x = GetMouseX() / PIXEL_SIZE;
	y = GetMouseY() / PIXEL_SIZE;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	board[x][y] = !board[x][y];
}

static void	draw_glider(Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if (x < 0 || x + 2 >= WIDTH || y < 0 || y + 2 >= HEIGHT)
		return ;
	DrawRectangle((x + 2) * PIXEL_SIZE, (y + 0) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle((x + 2) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle((x + 2) * PIXEL_SIZE, (y + 2) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle((x + 1) * PIXEL_SIZE, (y + 2) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle((x + 0) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

static void	put_glider(bool board[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if (x < 0 || x + 2 >= WIDTH || y < 0 || y + 2 >= HEIGHT)
		return ;
	board[x + 2][y + 0] = true;
	board[x + 2][y + 1] = true;
	board[x + 2][y + 2] = true;
	board[x + 1][y + 2] = true;
	board[x + 0][y + 1] = true;
}

static void	draw_blinker(Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if (x < 0 || x + 2 >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	DrawRectangle((x + 0) * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle((x + 1) * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle((x + 2) * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

static void	put_blinker(bool board[WIDTH][HEIGHT], Vector2 position)
{
	int	x;
	int	y;

	x = (int)position.x;
	y = (int)position.y;
	if (x < 0 || x + 2 >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	board[x + 0][y] = true;
	board[x + 1][y] = true;
	board[x + 2][y] = true;
}

int	main(void)
{
	Camera2D		camera;

	static bool		board[WIDTH][HEIGHT];
	static int		frameCount;
	static bool		isPaused = true;
	static int		delay;

	InitWindow(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, "GOL");
	initialise_scene(&camera);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BACKGROUND_COLOR);
		BeginMode2D(camera);
		draw_board(board);
		EndMode2D();
		if (isPaused)
			DrawText("Paused", WIDTH * PIXEL_SIZE - (8 * PIXEL_SIZE), 0,
						32, WHITE);
		if (IsKeyDown(KEY_G))
		{
			draw_glider((Vector2){GetMouseX() / PIXEL_SIZE,
									GetMouseY() / PIXEL_SIZE});
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				put_glider(board, (Vector2){GetMouseX() / PIXEL_SIZE,
											GetMouseY() / PIXEL_SIZE});
		}
		else if (IsKeyDown(KEY_B))
		{
			draw_blinker((Vector2){GetMouseX() / PIXEL_SIZE,
									GetMouseY() / PIXEL_SIZE});
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				put_blinker(board, (Vector2){GetMouseX() / PIXEL_SIZE,
											GetMouseY() / PIXEL_SIZE});
		}
		else if (IsKeyPressed(KEY_SPACE))
			isPaused = !isPaused;
		else if (IsKeyDown(KEY_COMMA) && UPDATE_RATE + delay < 20)
			++delay;
		else if (IsKeyDown(KEY_PERIOD) && UPDATE_RATE + delay > 1)
			--delay;
		else if (IsKeyDown(KEY_R))
			clear_board(board);
		else
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				click_on_the_board(board);
		DrawCircle(GetMouseX(), GetMouseY(), PIXEL_SIZE / 4, CURSOR_COLOR);
		EndDrawing();
		if (++frameCount % (UPDATE_RATE + delay) == 0 && !isPaused)
		{
			update_board(board);
			if (frameCount == 10000)
				frameCount = 0;
		}
	}
	CloseWindow();
	return (0);
}
