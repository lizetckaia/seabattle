//
// Created by eletc on 28.06.2022.
//

#ifndef UNTITLED1_FUNTIONFORTEST_H
#define UNTITLED1_FUNTIONFORTEST_H
const int N = 10;
const int NUM_SHIPS = 9;

/**
 * функция, которая возвращает целое значение в зависимости от того, ранен корабль, убит, или был совершен промах
 * @param map поле
 * @param x координата х
 * @param y координата у
 * @param ships ссылка на массив, в котором хранится информация о жизнях корабля
 * @param mask ссылка на маску
 * @return
 */

int shot(int map[N][N], int x, int y, int ships[NUM_SHIPS+1], int mask[N][N]);

#endif //UNTITLED1_FUNTIONFORTEST_H
