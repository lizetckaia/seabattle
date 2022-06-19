//#include 'stdafx.h'
#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    const int N = 10;

        while(true)
        {
            int map [N][N] = {0};

            int x, y;

            int dir = 0;

            int count_ship = 0;

            while(count_ship < 3)
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
                for (int i = 0; i < 5; i++)
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
                    for (int i = 0; i < 5; i++)
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
            getch();
        }

    return 0;
}
