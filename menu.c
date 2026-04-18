#include "menu.h"

void item_output(int  row_number, char* text, HANDLE handle, WORD color) {
    COORD cursor_position = { 50, row_number };
    SetConsoleTextAttribute(handle, color);
    SetConsoleCursorPosition(handle, cursor_position);
    printf("%s", text);
}

void item_activate(int row_number, char* text, HANDLE handle) {
    item_output(row_number, text, handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED);
}

void item_hide(int row_number, char* text, HANDLE handle) {
    item_output(row_number, text, handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY |
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void show_cursor(bool visible, HANDLE handle) {
    CONSOLE_CURSOR_INFO ccInfo;
    ccInfo.bVisible = visible;
    ccInfo.dwSize = 20;
    SetConsoleCursorInfo(handle, &ccInfo);
}

void select_item(int* active_item, struct menu_item* items, int item_count, HANDLE handle) {
    int i_key = 67;
    while (i_key != ENTER) {
        if (_kbhit()) {
            i_key = _getch();
            switch (i_key) {
            case KEY_ARROW_UP:
                if (*active_item > 0) {
                    item_hide(*active_item + 5, items[*active_item].text, handle);
                    (*active_item)--;
                    item_activate(*active_item + 5, items[*active_item].text, handle);
                }
                break;
            case KEY_ARROW_DOWN:
                if (*active_item < item_count - 1) {
                    item_hide(*active_item + 5, items[*active_item].text, handle);
                    (*active_item)++;
                    item_activate(*active_item + 5, items[*active_item].text, handle);
                }
                break;
            case ESC:
                exit(0);
            }
        }
    }
}
void main_menu(struct menu_item* items, int item_count) {
    COORD cursor_position;
    cursor_position.X = 10;
    int active_item = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    bool run = true;
    while (run) {
        system("cls");
        show_cursor(false, handle);
        for (int i = 0; i < item_count; i++) {
            item_hide(i + 5, items[i].text, handle);
        }
        item_activate(active_item + 5, items[active_item].text, handle);
        select_item(&active_item, items, item_count, handle);
        SetConsoleTextAttribute(handle, BACKGROUND_GREEN | BACKGROUND_INTENSITY |
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        system("cls");
        show_cursor(true, handle);
        items[active_item].handler();
        system("pause");
    }
}