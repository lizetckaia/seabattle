#include "funtionfortest.h"
#include <doctest.h>
using namespace std;

TEST_CASE("doctest works")
{
    REQUIRE(true);
}

TEST_CASE("shot")

{
    ///корабли, которые будут расставляться на поле игрока
    int ships[NUM_SHIPS+1] = {0, 4,3,3,2,2,2,1,1,1};

    ///карта, принадлежащая человеку
    int map [N][N] = {0};

    ///переменные, содержащие координаты, по которым стреляет человек
    int x = 0, y = 0;

    int mask [N][N] = {0};

    int result = 0;

    if (map[x][y] == -1 || map[x][y] == -2)
    {
        CHECK (result == 3);
    }

    else if (map[x][y] >= 1)
    {
        ships[map[x][y]]--;

        if (ships[map[x][y]] <= 0)
        {
            CHECK (result == 2);
        }

        else
        {
            CHECK (result == 1);
        }

    }

}
