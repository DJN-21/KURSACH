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
    for (int i = 0; text[i] != '\0'; i++) {

        unsigned char c1 = (unsigned char)text[i];
        if (c1 == 0xD0 && (unsigned char)text[i + 1] == 0x81) {
            text[i] = (char)0xD0; text[i + 1] = (char)0x95;
        }
        else if (c1 == 0xD1 && (unsigned char)text[i + 1] == 0x91) {
            text[i] = (char)0xD0; text[i + 1] = (char)0xB5;
            c1 = 0xD0;
        }
        if ((c1 >= 'A' && c1 <= 'Z') || (c1 >= 'a' && c1 <= 'z')) {
            unsigned char start = (c1 >= 'a') ? 'a' : 'A';
            int size = 26;
            int shift = (direction == 2) ? (size - (move % size)) : (move % size);
            text[i] = start + (c1 - start + shift) % size;
        }
        else if (c1 == 0xD0 || c1 == 0xD1) {
            unsigned char c2 = (unsigned char)text[i + 1];
            int unicode_code = ((c1 & 0x1F) << 6) | (c2 & 0x3F);
            int start = 0, size = 32;

            if (unicode_code >= 0x0410 && unicode_code <= 0x042F) {
                start = 0x0410;
            }
            else if (unicode_code >= 0x0430 && unicode_code <= 0x044F) {
                start = 0x0430;
            }

            if (start > 0) {
                int shift = (direction == 2) ? (size - (move % size)) : (move % size);
                int new_code = start + (unicode_code - start + shift) % size;
                text[i] = (char)(0xD0 | (new_code >> 6));
                text[i + 1] = (char)(0x80 | (new_code & 0x3F));
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
    char* buffer = malloc(fileSize + 1);
    size_t bytesRead = fread(buffer, 1, fileSize, fPtr);
    buffer[bytesRead] = '\0';
    fclose(fPtr);
    int move = input_int("Введите сдвиг для файла:");
    int direction = 0;
    while (direction < 1 || direction>2) {
        direction = input_int("Направление (1-Право, 2-Лево):");
        if (direction < 1 || direction>2) {
            puts("\nОшибка! Сдвиг может приниимать только значения 1 или 2!\n");
        }
       
    } 
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
    int move = input_int("Введите сдвиг: ");
    int direction = input_int("Направление (1-Право, 2-Лево): ");
    printf("РЕЗУЛЬТАТ: %s ------->",text);
    caesar_cipher(text, move, direction);
    printf("%s\n", text);
}
void about_cipher() {
    system("cls");
    printf("\n\n   _____                         \n");
    printf("  / ____|                        \n");
    printf(" | |     ___  ___  __ _ _ __     \n");
    printf(" | |    / _ \\/ __|/ _` | '__|    \n");
    printf(" | |___|  __/\\__ \\ (_| | |       \n");
    printf("  \\_____\\___||___/\\__,_|_|       \n\n");
    printf("=====================================\n");
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