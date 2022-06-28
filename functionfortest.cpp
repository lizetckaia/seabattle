#include <iostream>
#include "main.cpp"

/**
 * функция, выводящая игровое поле на экран
 * @param map поле
 * @param mask маска
 * @param use_mask накладывание маски
 */

void map_show(int map[N][N], int mask[N][N], bool use_mask)
{
    /**
     * прорисовка
     */
    cout << " ";

    for (int i = 0; i < N; i++)
    {
        cout << i;
    }
    cout << endl;

    for (int i = 0; i < N; i++)
    {
        cout << i;

        for (int j = 0; j < N; j++)
        {
            if (mask[j][i] == 1 || use_mask == 0)
            {
                if (map[j][i] == 0)
                {
                    cout << "-";
                }

                else if (map[j][i] == -1)
                {
                    cout << "X";
                }

                else if (map[j][i] == -2)
                {
                    cout << ".";
                }

                else
                {
                    cout << map[j][i];
                }
            }

            else
            {
                cout << ' ';
            }
        }
        cout << endl;
    }
}
