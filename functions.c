#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"
void Exit_prog() {
    puts("Программа завершена!");
    exit(0);
}
int input_int(char query[50]) {
    int number;
    int indicator = 1;
    while (indicator) {
        printf("%s ", query);
        if (scanf_s("%d", &number) != 1 || number < 0)
        {
            while (getchar() != '\n');
            puts("Ошибка - повторите ввод");
        }
        else {
            while (getchar() != '\n');
            indicator = 0;
        }
    }
    return number;
}

void caesar_cipher(char* text, int move, int direction) {
    const char* rus_up = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const char* rus_low = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    int rus_size = 33;
    for (int i = 0; text[i] != '\0'; i++) {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) {
            char start = (text[i] >= 'a') ? 'a' : 'A';
            int shift = (direction == 2) ? (26 - (move % 26)) : (move % 26);
            text[i] = start + (text[i] - start + shift) % 26;
        }
        else if ((unsigned char)text[i] == 0xD0 || (unsigned char)text[i] == 0xD1) {
            char current_char[3] = { text[i], text[i + 1], '\0' };
            char* p;
            int pos = -1;
            if ((p = strstr(rus_up, current_char))) pos = (p - rus_up) / 2;
            else if ((p = strstr(rus_low, current_char))) pos = (p - rus_low) / 2;
            if (pos != -1) {
                int shift = (direction == 2) ? (rus_size - (move % rus_size)) : (move % rus_size);
                int new_pos = (pos + shift) % rus_size;
                const char* target_alpha = (p >= rus_low) ? rus_low : rus_up;
                text[i] = target_alpha[new_pos * 2];
                text[i + 1] = target_alpha[new_pos * 2 + 1];
                i++;
            }
        }
    }
}
void file_chipher() {
    FILE* fPtr;
    fPtr = fopen("input.txt", "r");
    if ((fPtr == NULL)) {
        perror("Невозможно открыть файл!");
        return;
    }
    fseek(fPtr, 0, SEEK_END);
    int fileSize = ftell(fPtr);
    rewind(fPtr);
    if (fileSize <= 0) {
        puts("Ошибка: Файл input.txt пуст!");
        fclose(fPtr);
        return;
    }
    char* buffer = malloc(fileSize + 1);
    size_t bytesRead = fread(buffer, 1, fileSize, fPtr);
    buffer[bytesRead] = '\0';
    fclose(fPtr);
    int direction = 0;
    while (direction < 1 || direction>2) {
        direction = input_int("Процедура: \n [1]-Шифрование\n [2]-Дешифрование \n");
        if (direction < 1 || direction>2) {
            puts("\nОшибка!\n");
        }  
    }
    int move = input_int("Введите ключ шифрования (смещение):  ");
    caesar_cipher(buffer, move, direction);
    FILE* outPtr = fopen("output.txt", "w");
    if (outPtr != NULL) {
        fputs(buffer, outPtr);
        fclose(outPtr);
        puts("Готово! Результат в файле output.txt");
    }
    else {
        puts("Не удалось сохранить результат в файл.");
    }
    free(buffer);
}
void work() {
    char text[500];
    printf("Введите ваш текст: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    int direction = 0;
    while (direction < 1 || direction>2) {
         direction = input_int("Процедура: \n [1]-Шифрование\n [2]-Дешифрование \n");
        if (direction < 1 || direction>2) {
            puts("\nОшибка!\n");
        }

    }
    int move = input_int("Введите ключ шифрования (смещение): ");
    printf("РЕЗУЛЬТАТ:\n %s ===> ",text);
    caesar_cipher(text, move, direction);
    printf("%s\n", text);
}
void about_cipher() {
    system("cls");
    printf("\n\n\t\t\t\t======================================================================\n");
    printf("\t\t\t\t||   _____                            ____  _       _               ||\n");
    printf("\t\t\t\t||  / ____|                         / ____|(_)     | |              ||\n");
    printf("\t\t\t\t|| | |     ___  ___  __ _ _ __     | |      _ _ __ | |__   ___ _ __ ||\n");
    printf("\t\t\t\t|| | |    / _ \\/ __|/ _` | '__|    | |     | | '_ \\| '_ \\ / _ \\ '__|||\n");
    printf("\t\t\t\t|| | |___|  __/\\__ \\ (_| | |       | |____ | | |_) | | | |  __/ |   ||\n");
    printf("\t\t\t\t||  \\_____\\___||___/\\__,_|_|        \\_____||_| .__/|_| |_|\\___|_|   ||\n");
    printf("\t\t\t\t||                                           | |                    ||\n");
    printf("\t\t\t\t||                                           |_|                    ||\n");
    printf("\t\t\t\t======================================================================\n\n\n");
    printf("Шифр Цезаря — это один из самых простых\n");
    printf("и известных методов шифрования.\n\n");
    printf("Он работает путем сдвига букв алфавита\n");
    printf("на фиксированное число позиций.\n\n");
    printf("Пример:\n");
    printf("HELLO -> KHOOR\n\n");
    printf("Шифр назван в честь Юлия Цезаря,\n");
    printf("который использовал его для\n");
    printf("секретных сообщений.\n\n");
}
