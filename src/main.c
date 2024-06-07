/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 02:40:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2024/06/07 15:17:18 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "GOL.h"

int	mod(int n1, int n2)
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

static void	draw_board(Game *game)
{
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			if (game->board[i][j])
				DrawRectangle(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, game->foreground_color);
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

static void	initialise_game(Game *game)
{
	game->foreground_color = DEFAULT_FOREGROUND_COLOR;
	game->background_color = DEFAULT_BACKGROUND_COLOR;
	game->drawing_color = ColorAlpha(DEFAULT_DRAWING_COLOR, 0.75);
	game->cursor_color = DEFAULT_CURSOR_COLOR;
	game->isPaused = true;
	game->keyPatternAmount[G] = 2;
	game->keyPatternAmount[B] = 1;
	HideCursor();
	SetTargetFPS(FPS);
}

int	change_speed(int speed)
{
	if (IsKeyDown(KEY_COMMA) && UPDATE_RATE + speed < 60)
		++speed;
	if (IsKeyDown(KEY_PERIOD) && UPDATE_RATE + speed > 1)
		--speed;
	return (speed);
}

void	handle_pattern_selection(Game *game)
{
	if (IsKeyPressed(KEY_G))
	{
		for (int i = 0; i < MAX_USED_KEYS; ++i)
		{
			if (game->isKeyUsed[i] != game->isKeyUsed[G])
			{
				game->isKeyUsed[i] = false;
				game->keyUsedCounter[i] = 0;
			}
		}
		game->isKeyUsed[G] = true;
		if (!IsKeyDown(KEY_LEFT_SHIFT))
		{
			if (game->keyUsedCounter[G]++ % 60 == game->keyPatternAmount[G])
				game->keyUsedCounter[G] = 0;
		}
		else
		{
			if (--game->keyUsedCounter[G] < 0)
				game->keyUsedCounter[G] = game->keyPatternAmount[G];
		}
	}
	else if (IsKeyPressed(KEY_B))
	{
		for (int i = 0; i < MAX_USED_KEYS; ++i)
		{
			if (game->isKeyUsed[i] != game->isKeyUsed[B])
			{
				game->isKeyUsed[i] = false;
				game->keyUsedCounter[i] = 0;
			}
		}
		game->isKeyUsed[B] = true;
		if (!IsKeyDown(KEY_LEFT_SHIFT))
		{
			if (game->keyUsedCounter[B]++ % 60 == game->keyPatternAmount[B])
				game->keyUsedCounter[B] = 0;
		}
		else
		{
			if (--game->keyUsedCounter[B] < 0)
				game->keyUsedCounter[B] = game->keyPatternAmount[B];
		}
	}
}

void	draw_pattern(Game *game)
{
	if (game->isKeyUsed[G])
	{
		switch (game->keyUsedCounter[G] % (game->keyPatternAmount[G] + 1))
		{
			case 1:
				draw_glider((Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE}, game->drawing_color);
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
					put_glider(game->board, (Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
				draw_pattern_name("Glider", GetMousePosition(), game->isPaused);
				break;
			case 2:
				draw_gospel_gun_glider((Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE}, game->drawing_color);
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
					put_gospel_gun_glider(game->board, (Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
				draw_pattern_name("Gospel Gun Glider", GetMousePosition(), game->isPaused);
				break;
			default:
				game->isKeyUsed[G] = false;
				break;
		}
	}
	else if (game->isKeyUsed[B])
	{
		switch (game->keyUsedCounter[B] % (game->keyPatternAmount[B] + 1))
		{
			case 1:
				draw_blinker((Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE}, game->drawing_color);
				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
					put_blinker(game->board, (Vector2){GetMouseX() / PIXEL_SIZE, GetMouseY() / PIXEL_SIZE});
				draw_pattern_name("Blinker", GetMousePosition(), game->isPaused);
				break ;
			default:
				game->isKeyUsed[B] = false;
				break ;
		}
	}
	else
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			put_cell(game->board, ALIVE);
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			put_cell(game->board, DEAD);
	}
}

int	main(void)
{
	static Game game;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GOL");
	initialise_game(&game);
	while (!WindowShouldClose())
	{
		if (++game.frameCount % (UPDATE_RATE + game.speed) == 0 && !game.isPaused)
		{
			update_board(game.board);
			if (game.frameCount == 10000)
				game.frameCount = 0;
		}
		if (game.isPaused)
			DrawText("Paused", SCREEN_WIDTH - PIXEL_SIZE * 8, 0, PIXEL_SIZE * 2, WHITE);
		if (IsKeyPressed(KEY_SPACE))
			game.isPaused = !game.isPaused;
		if (IsKeyDown(KEY_R))
			clear_board(game.board);
		game.speed = change_speed(game.speed);
		handle_pattern_selection(&game);
		BeginDrawing();
		{
			ClearBackground(game.background_color);
			draw_board(&game);
			draw_pattern(&game);
			DrawCircle(GetMouseX(), GetMouseY(), PIXEL_SIZE / 4, game.cursor_color);
		}
		EndDrawing();
	}
	CloseWindow();
	return (0);
}
