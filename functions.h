#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void Exit_prog();
int input_int(char query[50]);
void work();
void caesar_cipher(char* text, int move, int direction);
void file_chipher();
void about_cipher();