#pragma once

#include <Windows.h>
#include <stdbool.h>
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define ENTER 13
#define ESC 27
typedef void (*Handler)();
struct menu_item
{
	char* text;
	Handler handler;
};
void main_menu(struct menu_item* items, int item_count);