/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:40:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/06 21:07:25 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 150		// Width of the board
#define HEIGHT 80		// Height of the board
#define PIXEL_SIZE 8	// Size of each pixel
#define UPDATE_RATE 10	// Update rate of the board
#define FPS 60			// Frames Per Second
#define SCREEN_WIDTH (WIDTH * PIXEL_SIZE)
#define SCREEN_HEIGHT (HEIGHT * PIXEL_SIZE)

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

static int	mod(int n1, int n2)
{
	return ((n1 + n2) % n2);
}

static int	count_neighbours(bool board[WIDTH][HEIGHT], Vector2 position)
{
	int	neighbour;
	int	x;
	int	y;

	neighbour = 0;
	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (i == 0 && j == 0)
				continue;
			x = mod((int)position.x + i, WIDTH);
			y = mod((int)position.y + j, HEIGHT);
			if (board[x][y])
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
				DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

static void	clear_board(bool board[WIDTH][HEIGHT])
{
	for (int i = 0; i < WIDTH; ++i)
		memset(board[i], false, HEIGHT);
}

static void	update_board(bool board[WIDTH][HEIGHT])
{
	static bool	temp[WIDTH][HEIGHT];
	int			neighbours;

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

//       012
//    
//    0  OOO
static void	draw_blinker(Vector2 position)
{
	int	x;
	int	y;
	int	offset;

	x = (int)position.x;
	y = (int)position.y;
	offset = -1;
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

//       012
//    
//    0  ..O
//    1  O.O
//    2  .OO
static void	draw_glider(Vector2 position)
{
	int	x;
	int	y;
	int	offset;

	x = mod((int)position.x, WIDTH);
	y = mod((int)position.y, HEIGHT);
	offset = -1;
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 2 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + offset + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

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
static void	draw_gospel_gun_glider(Vector2 position)
{
	int	x;
	int	y;
	int	offset;

	x = mod((int)position.x, WIDTH);
	y = mod((int)position.y, HEIGHT);
	offset = -18;

	// 0
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 0 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 1 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);

	// 1
	DrawRectangle(mod(x + 10 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 10 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 10 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 11 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 12 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 4 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 13 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 4 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 15 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 16 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 16 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 17 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 14 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 16 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 15 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 13 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 12 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 11 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);

	// 2
	DrawRectangle(mod(x + 20 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 20 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 20 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 21 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 21 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 21 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 0 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 22 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 22 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 3 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 4 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 24 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y + 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);

	// 3
	DrawRectangle(mod(x + 34 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 34 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 35 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 1 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
	DrawRectangle(mod(x + 35 + offset + WIDTH, WIDTH) * PIXEL_SIZE, mod(y - 2 + HEIGHT, HEIGHT) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, FOREGROUND_COLOR);
}

static void	put_gospel_gun_glider(bool board[WIDTH][HEIGHT], Vector2 position)
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

static void	put_glider(bool board[WIDTH][HEIGHT], Vector2 position)
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

static void	put_blinker(bool board[WIDTH][HEIGHT], Vector2 position)
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

static void	put_cell(bool board[WIDTH][HEIGHT], bool state)
{
	int	x;
	int	y;

	x = GetMouseX() / PIXEL_SIZE;
	y = GetMouseY() / PIXEL_SIZE;
	board[x][y] = state;
}

static void	draw_pattern_name(const char *name, Vector2 mousePosition, bool isPaused)
{
	int	name_length;
	int	offset;

	if (!isPaused)
		return ;
	name_length = strlen(name);
	offset = name_length / 2;
	if (name_length % 2 != 0)
		++name_length;
	if (mousePosition.y - SCREEN_HEIGHT / 2 >= 0)
		DrawText(name, SCREEN_WIDTH / 2 - (name_length + offset) / 2 * PIXEL_SIZE, 0, PIXEL_SIZE * 3, RAYWHITE);
	else
		DrawText(name, SCREEN_WIDTH / 2 - (name_length + offset) / 2 * PIXEL_SIZE, SCREEN_HEIGHT - PIXEL_SIZE * 3, PIXEL_SIZE * 3, RAYWHITE);
}

int	main(void)
{
	static bool		board[WIDTH][HEIGHT];
	static int		frameCount;
	static bool		isPaused = true;
	static int		delay;
	static bool		isKeyUsed[MAX_USED_KEYS];
	static int		keyUsedCounter[MAX_USED_KEYS];
	static int		keyPatternAmount[MAX_USED_KEYS];

	keyPatternAmount[G] = 2;
	keyPatternAmount[B] = 1;
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GOL");
	HideCursor();
	SetTargetFPS(FPS);
	while (!WindowShouldClose())
	{
		if (++frameCount % (UPDATE_RATE + delay) == 0 && !isPaused)
		{
			update_board(board);
			if (frameCount == 10000)
				frameCount = 0;
		}
		if (isPaused)
			DrawText("Paused", SCREEN_WIDTH - PIXEL_SIZE * 8, 0, PIXEL_SIZE * 2, WHITE);
		if (IsKeyPressed(KEY_SPACE))
			isPaused = !isPaused;
		if (IsKeyDown(KEY_COMMA) && UPDATE_RATE + delay < 20)
			++delay;
		if (IsKeyDown(KEY_PERIOD) && UPDATE_RATE + delay > 1)
			--delay;
		if (IsKeyPressed(KEY_G))
		{
			for (int i = 0; i < MAX_USED_KEYS; ++i)
			{
				if (isKeyUsed[i] != isKeyUsed[G])
				{
					isKeyUsed[i] = false;
					keyUsedCounter[i] = 0;
				}
			}
			isKeyUsed[G] = true;
			if (!IsKeyDown(KEY_LEFT_SHIFT))
			{
				if (keyUsedCounter[G]++ % 60 == keyPatternAmount[G])
					keyUsedCounter[G] = 0;
			}
			else
			{
				if (--keyUsedCounter[G] < 0)
					keyUsedCounter[G] = keyPatternAmount[G];
			}
		}
		else if (IsKeyPressed(KEY_B))
		{
			for (int i = 0; i < MAX_USED_KEYS; ++i)
			{
				if (isKeyUsed[i] != isKeyUsed[B])
				{
					isKeyUsed[i] = false;
					keyUsedCounter[i] = 0;
				}
			}
			isKeyUsed[B] = true;
			if (!IsKeyDown(KEY_LEFT_SHIFT))
			{
				if (keyUsedCounter[B]++ % 60 == keyPatternAmount[B])
					keyUsedCounter[B] = 0;
			}
			else
			{
				if (--keyUsedCounter[B] < 0)
					keyUsedCounter[B] = keyPatternAmount[B];
			}
		}
		BeginDrawing();
		{
			ClearBackground(BACKGROUND_COLOR);
			draw_board(board);
			if (isKeyUsed[G])
			{
				switch (keyUsedCounter[G] % (keyPatternAmount[G] + 1))
				{
					case 0:
						isKeyUsed[G] = false;
						break;
					case 1:
						draw_glider((Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
						if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
							put_glider(board, (Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
						draw_pattern_name("Glider", GetMousePosition(), isPaused);
						break;
					case 2:
						draw_gospel_gun_glider((Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
						if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
							put_gospel_gun_glider(board, (Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
						draw_pattern_name("Gospel Gun Glider", GetMousePosition(), isPaused);
						break;
				}
			}
			else if (isKeyUsed[B])
			{
				switch (keyUsedCounter[B] % (keyPatternAmount[B] + 1))
				{
					case 0:
						isKeyUsed[B] = false;
						break ;
					case 1:
						draw_blinker((Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
						if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
							put_blinker(board, (Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
						draw_pattern_name("Blinker", GetMousePosition(), isPaused);
						break ;
				}
			}
			else
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
					put_cell(board, ALIVE);
				if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
					put_cell(board, DEAD);
			}
			if (IsKeyDown(KEY_R))
				clear_board(board);
			DrawCircle(GetMouseX(), GetMouseY(), PIXEL_SIZE / 4, CURSOR_COLOR);
		}
		EndDrawing();
	}
	CloseWindow();
	return (0);
}
