//#include 'stdafx.h'
#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const int N = 10;

//функция, ставящая на поле корабли
//три параметра: поле, размер корабля, количество кораблей
void set_ships_rand(int map[N][N],int ship_size, int ships_num)
{
    int x, y;

    int dir = 0;

    int count_ship = 0;

    while(count_ship < ships_num)
    {
        //первичная позиция кораблей
        x = rand() % N;
        y = rand() % N;

        int temp_x = x;
        int temp_y = y;

        bool setting_is_possible = 1;
        //генерация направления кораблей
        dir = rand() % 4;
        //проверка возможности постановки корабля
        for (int i = 0; i < ship_size; i++)
        {
            if (x < 0 || y < 0 || x >= N || y >= N)
            {
                setting_is_possible = 0;
                break;
            }

            if (map[x  ][y]   == 1 ||
                map[x  ][y+1] == 1 ||
                map[x  ][y-1] == 1 ||
                map[x+1][y]   == 1 ||
                map[x+1][y+1] == 1 ||
                map[x+1][y-1] == 1 ||
                map[x-1][y]   == 1 ||
                map[x-1][y+1] == 1 ||
                map[x-1][y-1] == 1)
            {
                setting_is_possible = 0;
                break;
            }

            switch(dir)
            {
                case 0:
                    x++;
                    break;
                case 1:
                    y++;
                    break;
                case 2:
                    x--;
                    break;
                case 3:
                    y--;
                    break;
            }
        }

        //ставим корабль, если есть такая возможность
        if (setting_is_possible == 1)
        {
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < ship_size; i++)
            {
                switch(dir)
                {
                    case 0:
                        map[x][y] = 1;
                        x++;
                        break;
                    case 1:
                        map[x][y] = 1;
                        y++;
                        break;
                    case 2:
                        map[x][y] = 1;
                        y--;
                        break;
                }
            }
            count_ship++;
        }
    }
}

//основная функция
int main()
{
        while(true)
        {
            int map [N][N] = {0};

            //добавляем корабли
            set_ships_rand(map, 4, 1);

            set_ships_rand(map, 3, 2);

            set_ships_rand(map, 3, 2);

            set_ships_rand(map, 1, 4);

            //прорисовка корабля
            for (int i = 1; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (map[j][i] == 0)
                    {
                        cout << "-";
                    }
                    else
                    {
                        cout << map[j][i];
                    }
                }
                cout << endl;
            }
            break;
        }

    return 0;
}
