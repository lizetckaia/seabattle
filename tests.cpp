#include "functionfortest.cpp"
#include <doctest.h>
using namespace std;

TEST_CASE("doctest works")
{
    REQUIRE(true);
}

TEST_CASE("testing map_show")
{

}

TEST_CASE("shot")

{
    int shot;

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
        map[x][y] = -1;
    }

}
