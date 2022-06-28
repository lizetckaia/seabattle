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

    int result = shot(map, x, y, ships, mask);
    CHECK(result == 0);



}
