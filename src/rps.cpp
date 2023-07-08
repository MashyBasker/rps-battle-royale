#include "rps.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>

#define HEIGHT 50
#define WIDTH 100

/// global data
static const std::string symbol = "■";
int ground[HEIGHT][WIDTH];

/// function prototypes
void generate_battleground();
void print_color(int data);
void display_arena();

/// Main function
int main()
{
    srand(time(0));
    generate_battleground();
    display_arena();
    return 0;
}

/// Helper functions

// generates the initial state of the game field
void generate_battleground()
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            ground[y][x] = rand() % 3;
        }
    }
}

// displays symbol based on color
// 0 --> Rock    ==> BOLDYELLOW
// 1 --> Paper   ==> BOLDWHITE
// 2 --> Scissor ==> BOLDCYAN
void print_color(int data)
{
    if (data == 0) {
        std::cout << BOLDYELLOW << symbol << RESET;
    } else if (data == 1) {
        std::cout << BOLDWHITE << symbol << RESET;
    } else if (data == 2) {
        std::cout << BOLDRED << symbol << RESET;
    } else {
        std::cout << "";
    }
}

void display_arena()
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            print_color(ground[y][x]);
        }
        std::cout << '\n';
    }
}
