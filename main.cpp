#include <iostream>
#include <cmath>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>

using namespace std;

const int N = 10;
const int NUM_SHIPS = 9;

//функция, ставящая на поле корабли
//три параметра: поле, размер корабля, идентификатор корабля
void set_ships_rand(int map[N][N],int ship_size, int ship_id)
{
    int x, y;

    int dir = 0;

    int count_ship = 0;

    int count_tact = 0;

    while(count_ship < 1)
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
                map[x][y] = ship_id;

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
            count_ship++;
        }
    }
}

//функция, выводящая игровое поле на экран
//параметры: исходный массив и маска
void map_show(int map[N][N], int mask[N][N], bool use_mask)
{
    //прорисовка
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
//функция, которая возвращает целое значение в зависимости от того ранен корабль, убит или был совершен промах
//параметры: ссылка на карту, координата x, координата y, ссылка на массив, в котором хранится информация о жизнях корабля, ссылка на маску
int shot(int map[N][N], int x, int y, int ships[NUM_SHIPS+1], int mask[N][N])
{
    int result = 0; //переменная, которая отвечает за результат стрельбы

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

//основная функция
int main()
{
    while(true)
    {
        int map [N][N] = {0}; //карта, принадлежащая человеку
        int map2 [N][N] = {0}; //карта, принадлежащая компьютеру

        int ships1[NUM_SHIPS+1] = {0, 4,3,3,2,2,2,1,1,1}; //корабли, которые будут расставляться на поле человека (1 4-х палубный корабль, 2 3-х палубных корабля, 3 2-х палубных корабля, 3 1-х палубных корабля)
        int ships2[NUM_SHIPS+1] = {0, 4,3,3,2,2,2,1,1,1}; //корабли, которые будут расставляться на поле компьютера (1 4-х палубный корабль, 2 3-х палубных корабля, 3 2-х палубных корабля, 3 1-х палубных корабля)


        int mask [N][N] = {0};
        int mask2 [N][N] = {0};

        //добавляем корабли
        for (int i = 1; i <= NUM_SHIPS; i++)
        {
            set_ships_rand(map, ships1[i], i);
        }
        for (int i = 1; i <= NUM_SHIPS; i++)
        {
            set_ships_rand(map2, ships2[i], i);
        }

        int x = 0, y = 0; //переменные, содержащие координаты, по которым стреляет человек

        int first_hit_x = 0; //переменная, хранящая координату x первого попадания по кораблю
        int first_hit_y = 0; //переменная, хранящая координату y первого попадания по кораблю

        int mode = 0; //переменная, определяющая режим работы бота

        int x_bot = 0; //переменная, содержащая координату x, по которой стреляет бот
        int y_bot = 0; //переменная, содержащая координату y, по которой стреляет бот

        int dir = 0;

        vector <int> dirs; //вектор направления

        dirs.push_back(3);
        dirs.push_back(2);
        dirs.push_back(1);
        dirs.push_back(0);

        bool win_gamer = 0;
        bool win_bot = 0;

        bool turn = 1; //переменная, отвечающая за очередность ходов(1 - ходит человек, 0 - компьютер)

        //цикл, отвечающий за стрельбу
        while (win_gamer == false && win_bot == false)
        {
            int result_shot = 0;
            //цикл, отвечающий за переключение хода
            do
            {
                map_show(map, mask, 0);
                cout << endl;
                map_show(map2, mask2, 1);

                if (turn == 1) //предоставление хода человеку
                {
                    cout << endl << "Enter coordinates";
                    cin >> x;
                    cin >> y;
                    result_shot = shot(map2, x, y, ships2, mask2);

                    if (result_shot == 1)
                    {
                        cout << "True" << endl;
                    }

                    else if (result_shot == 2)
                    {
                        bool died = 1;
                        for (int i = 1; i <= NUM_SHIPS; i++)
                        {
                            if (ships2[i] != 0)
                            {
                                died = 0;
                                break;
                            }
                        }
                        if (died == 1)
                        {
                            win_gamer =1;
                            break;
                        }

                        cout << "Killed" << endl;
                    }
                    else
                    {
                        cout << "False" << endl;
                    }
                }
                else //предоставление хода компьютеру
                {
                    cout << endl << "Computer's turn";
                    Sleep(1000); //компьютер думает

                    if (mode == 0)
                    {
                        do
                        {
                            x_bot = rand() % N;
                            y_bot = rand() % N;

                            result_shot = shot(map, x_bot, y_bot, ships1, mask);
                        } while(result_shot == 3);


                        if (result_shot == 1)
                        {
                            mode = 1;

                            first_hit_x = x_bot; //запоминание координаты x палубы корабля, по которой было осуществлено попадание
                            first_hit_y = y_bot; //запоминание координаты y палубы корабля, по которой было осуществлено попадание

                            if (!dirs.empty())
                            {
                                dir = dirs[dirs.size()-1];
                                dirs.pop_back();
                            }

                            cout << "True" << endl;
                        }

                        else if (result_shot == 2)
                        {
                            bool died = 1;
                            for (int i = 1; i <= NUM_SHIPS; i++)
                            {
                                if (ships1[i] != 0)
                                {
                                    died = 0;
                                    break;
                                }
                            }
                            if (died == 1)
                            {
                                win_bot =1;
                                break;
                            }

                            cout << "Killed" << endl;
                        }
                        else
                        {
                            cout << "False" << endl;
                        }

                    }
                    else if (mode == 1)
                    {
                        bool change_dir = 0;

                        if (dir == 0) // движение влево
                        {
                            if (x_bot > 0)
                                x_bot--;
                            else
                            {
                                change_dir = 1;
                            }
                        }
                        else if (dir == 1) //движение вправо
                        {
                            if (x_bot < N-1)
                                x_bot++;
                            else
                            {
                                change_dir = 1;
                            }
                        }
                        else if (dir == 2) //движение вверх
                        {
                            if (y_bot > 0)
                                y_bot--;
                            else
                            {
                                change_dir = 1;
                            }
                        }
                        else if (dir == 3) //движение вниз
                        {
                            if (y_bot < N-1)
                                y_bot++;
                            else
                            {
                                change_dir = 1;
                            }
                        }
                        if (change_dir == 1)
                        {
                            if (!dirs.empty())
                            {
                                dir = dirs[dirs.size()-1];
                                dirs.pop_back();
                            }
                            x_bot = first_hit_x;
                            y_bot = first_hit_y;

                            continue;
                        }
                        result_shot = shot(map, x_bot, y_bot, ships1, mask);

                        if (result_shot == 1)
                        {
                            cout << "True" << endl;
                        }
                        else if (result_shot == 2)
                        {
                            mode = 0;

                            dirs.clear();

                            dirs.push_back(3);
                            dirs.push_back(2);
                            dirs.push_back(1);
                            dirs.push_back(0);

                            bool died = 1;
                            for (int i = 1; i <= NUM_SHIPS; i++)
                            {
                                if (ships1[i] != 0)
                                {
                                    died = 0;
                                    break;
                                }
                            }
                            if (died == 1)
                            {
                                win_bot =1;
                                break;
                            }

                            cout << "Killed" << endl;
                        }
                        else
                        {
                            if (!dirs.empty())
                            {
                                dir = dirs[dirs.size()-1];
                                dirs.pop_back();
                            }
                            x_bot = first_hit_x;
                            y_bot = first_hit_y;

                            cout << "False" << endl;
                        }
                    }
                }



                Sleep(1000);
                system("cls");

            } while (result_shot != 0);
            turn = !turn;//передача хода
        }

        if (win_gamer == true)
        {
            cout << "You won!" << endl;
        }
        else if (win_bot == true)
        {
            cout << "Game over" << endl;
        }

        getch();
        system("cls");
    }
}
