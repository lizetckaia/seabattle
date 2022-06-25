#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <math.h>
//#include "stdafx.h"

using namespace std;

const int N = 10;

int ships_id = 1;
int ships[10] = {0};

//функция, которая переставляет курсор в заданные координаты
void gotoxy(int x, int y)
{
    COORD p = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
//функция, показывающая корабль в зависимости от параметров
//параметры: координата x, координата y, положение корабля, размер корабля
void ship_show(int x, int y, int dir, int ship_size)
{
    for (int i = 0; i < ship_size; i++)
    {
        gotoxy(x+1 ,y+1);
        cout << '#';

        switch (dir)
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
}
//функция проверки нахождения корабля в пределах карты
bool ship_in_map(int x, int y, int dir, int ship_size)
{
    bool in_map = 1;
    //генерация направления кораблей
    dir = rand() % 4;
    //проверка возможности постановки корабля
    for (int i = 0; i < ship_size; i++)
    {
        if (x < 0 || y < 0 || x >= N || y >= N)
        {
            in_map = 0;
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
    return in_map;
}
//установился ли корабль
bool set_ship(int map[N][N], int x, int y, int dir, int ship_size)
{
    int temp_x = x;
    int temp_y = y;

    bool setting_is_possible = 1;
    //проверка возможности постановки корабля
    for (int i = 0; i < ship_size; i++)
    {
        if (x < 0 || y < 0 || x >= N || y >= N)
        {
            setting_is_possible = 0;
            break;
        }

//if (map[x  ][y]   >= 1 ||
//map[x  ][y+1] >= 1 ||
//map[x  ][y-1] >= 1 ||
//map[x+1][y]   >= 1 ||
//map[x+1][y+1] >= 1 ||
//map[x+1][y-1] >= 1 ||
//map[x-1][y]   >= 1 ||
//map[x-1][y+1] >= 1 ||
//map[x-1][y-1] >= 1)
//{
//setting_is_possible = 0;
//break;
//}

        if (map[x][y]   >= 1)
        {
            setting_is_possible = 0;
            break;
        }
        if (y < N-1)
            if (map[x  ][y+1] >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (y > 0)
            if (map[x  ][y-1] >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (x < N-1)
            if (map[x+1][y]   >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (x < N-1 && y < N-1)
            if (map[x+1][y+1] >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (x < N-1 && y > 0)
            if (map[x+1][y-1] >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (x >0)
            if (map[x-1][y]   >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (x > 0 && y < N-1)
            if (map[x-1][y+1] >= 1)
            {
                setting_is_possible = 0;
                break;
            }
        if (x > 0 && y > 0)
            if (map[x-1][y-1] >= 1)
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
            map[x][y] = ships_id;

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
        ships[ships_id] = ship_size;

        ships_id++;
    }

    return setting_is_possible;
}

//функция, ставящая на поле корабли
//три параметра: поле, размер корабля, количество кораблей

void set_ships_rand(int map[N][N],int ship_size, int ships_num)
{
    int x, y;

    int dir = 0;

    int count_ship = 0;

    int count_tact = 0;

    while(count_ship < ships_num)
    {
        count_tact++;
        if (count_tact > 1000)
        {
            break;
        }

        //первичная позиция кораблей
        x = rand() % N;
        y = rand() % N;

        int temp_x = x;
        int temp_y = y;

        bool setting_is_possible = 1;
        //генерация направления кораблей
        dir = rand() % 4;

        bool settings_is_possible = 1;
        //проверка возможности постановки корабля
        for (int i = 0; i < ship_size; i++)
        {
            if (x < 0 || y < 0 || x >= N || y >= N)
            {
                setting_is_possible = 0;
                break;
            }

            if (map[x  ][y]   >= 1 ||
                map[x  ][y+1] >= 1 ||
                map[x  ][y-1] >= 1 ||
                map[x+1][y]   >= 1 ||
                map[x+1][y+1] >= 1 ||
                map[x+1][y-1] >= 1 ||
                map[x-1][y]   >= 1 ||
                map[x-1][y+1] >= 1 ||
                map[x-1][y-1] >= 1)
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
                map[x][y] = ships_id;

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
            ships[ships_id] = ship_size;

            ships_id++;
            count_ship++;
        }
    }
}

//функция, выводящая игровое поле на экран
//параметры: исходный массив и маска
void map_show(int map[N][N], int mask[N][N])
{
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
            //if (mask[j][i] == 1)
            {
                if (map[j][i] == 0)
                {
                    cout << "-";
                }
                else if (map[j][i] == -1)
                {
                    cout << "X";
                }
                else
                {
                    cout << map[j][i];
                }
            }
            //else
            //{
            //cout << ' ';
            //}
        }
        cout << endl;
    }
}

//основная функция
int main()
{
    while(true)
    {
        int map [N][N] = {0};
        int mask [N][N] = {0};
        //добавляем корабли

        //set_ships_rand(map, 4, 1);
        //set_ships_rand(map, 3, 2);
        //set_ships_rand(map, 2, 3);
        //set_ships_rand(map, 1, 3);

        int x = 2, y = 2; //координаты первой палубы корабля
        int dir = 1; //определяет положение корабля
        int ship_size = 4; //размер корабля
        int ch;

        while (true)
        {
            map_show(map,mask);
            ship_show(x, y, dir, ship_size);

            int temp_x = x;
            int temp_y = y;
            int temp_dir = dir;

            ch = _getch();

            //изменить координаты или направление
            switch (ch)
            {
                case 100: //d вправо
                    x++;
                break;
                case 115://s вниз
                    y++;
                break;
                case 97://a влево
                    x--;
                break;
                case 119://w вверх
                    y--;
                break;
                case 114://r поворот
                    dir = !dir;
                break;
                case 13://установка корабля
                    if (set_ship(map, x, y, dir, ship_size))
                    {
                        x = 0;
                        y = 0;
                        dir = 0;
                        ship_size--;
                    }
                    break;
            }

            if (!ship_in_map(x, y, dir, ship_size))
            {
                int x = temp_x;
                int y = temp_y;
                int dir = temp_dir;
            }



            system("cls");
        }

        while (true)
        {
            map_show(map,mask);
            cout << endl << "Enter coordinates" << endl;

            cin >> x;
            cin >> y;

            if (map[x][y] >= 1)
            {
                ships[map[x][y]]--;

                if (ships[map[x][y]] <= 0) {
                    cout << "Killed" << endl;
                }
                else
                {
                    cout << "True" << endl;
                }
                map[x][y] = -1;

                mask[x][y] = 1;
                bool ship_detect = false;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        if (map[i][j] == 1)
                        {
                            ship_detect = true;
                            break;
                        }
                    }
                    if (ship_detect)
                    {
                        break;
                    }
                }
                if (!ship_detect)
                {
                    cout << "You won!" << endl;
                    break;
                }
            }
            else
            {
                cout << "False" << endl;
            }
            mask[x][y] = 1;
        }
        break;

    }
    return 0;
}
