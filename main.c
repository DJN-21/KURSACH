#include <windows.h> 
#include <locale.h>
#include "menu.h"
#include "functions.h"
int main() {
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	setlocale(LC_ALL, ".UTF8");
	struct menu_item menu_items[4] =
	{
	"( Старт )", work,
	"( Работа с файлом )",file_chipher,
	"( Информация о  шифре )", about_cipher,
	"( Выход )",Exit_prog
	};
	main_menu(menu_items, 4);
	return 0;
}
