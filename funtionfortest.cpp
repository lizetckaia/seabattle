#include "funtionfortest.h"


/**
 * функция, которая возвращает целое значение в зависимости от того, ранен корабль, убит, или был совершен промах
 * @param map поле
 * @param x координата х
 * @param y координата у
 * @param ships ссылка на массив, в котором хранится информация о жизнях корабля
 * @param mask ссылка на маску
 * @return
 */

int shot(int map[N][N], int x, int y, int ships[NUM_SHIPS+1], int mask[N][N])
{
    ///переменная, которая отвечает за результат стрельбы
    int result = 0;

    if (map[x][y] == -1 || map[x][y] == -2)
    {
        result = 3;
    }

    else if (map[x][y] >= 1)
    {
        ships[map[x][y]]--;

        if (ships[map[x][y]] <= 0)
        {
            result = 2;
        }

        else
        {
            result = 1;
        }

        map[x][y] = -1;
    }

    else
    {
        map[x][y] = -2;
    }

    mask[x][y] = 1;

    return result;
}
