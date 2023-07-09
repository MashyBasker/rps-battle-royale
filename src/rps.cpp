#include "rps.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <time.h>
#include <vector>

#define HEIGHT 50
#define WIDTH 100

/// global data
static const std::string symbol = "■";
static int ground[HEIGHT][WIDTH] = { 0 };
static long long rock_count = 0;
static long long paper_count = 0;
static long long scissor_count = 0;

/// function prototypes
void generate_battleground();
void print_color(int data);
void display_arena();
void rock(std::vector<std::vector<int>> surr_state);
void paper(std::vector<std::vector<int>> surr_state);
void scissor(std::vector<std::vector<int>> surr_state);
void game_logic(int y, int x);
void update_game_arena();

/// Main function
int main()
{
    // init
    srand(time(0));
    generate_battleground();
    display_arena();
    // battle loop
    while (1) {

        // run the game loop
        update_game_arena();
        // display game arena
        display_arena();
        // rest a bit
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

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

// displays the current state of the arena
void display_arena()
{
    int ret = system("clear");
    if(ret == -1) {
        perror("Error: Could not clear screen");
    }
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            print_color(ground[y][x]);
        }
        std::cout << '\n';
    }
}

// identifier for rock is 0
// rock beats scissor
void rock(std::vector<std::vector<int>> surr_state)
{
    // implement the rock
    for (auto s : surr_state) {
        // if scissor is in the surrounding
        // then change it to rock
        if (ground[s[0]][s[1]] == 2) {
            ground[s[0]][s[1]] = 0;
            // update the count of the respective armies
            rock_count++;
            scissor_count--;
        }
        // do nothing if another rock
        // or paper is in the surrounding
    }
}

// identifier for paper is 1
// paper beats rock
void paper(std::vector<std::vector<int>> surr_state)
{
    // implement the paper
    for (auto s : surr_state) {
        // if rock is in the surrounding
        // then change it to a paper
        if (ground[s[0]][s[1]] == 0) {
            ground[s[0]][s[1]] = 1;
            // update the counts of the respective armies
            paper_count++;
            rock_count--;
        }
        // do nothing if another paper
        // or scissor is in the surrounding
    }
}

// identifier for scissor is 2
// scissor beats paper
void scissor(std::vector<std::vector<int>> surr_state)
{
    // implement the scissor
    for (auto s : surr_state) {
        // if paper is in the surrounding
        // then change it to a scissor
        if (ground[s[0]][s[1]] == 1) {
            ground[s[0]][s[1]] = 2;
            // update the counts of respective armies
            scissor_count++;
            paper_count--;
        }
        // do nothing if another scissor
        // or rock is in the surrounding
    }
}

// the RPS game logic
void game_logic(int y, int x)
{
    // store current state
    int curr_state = ground[y][x];
    // store surrounding states
    std::vector<std::vector<int>> surr_state {
        { y - 1, x }, // up
        { y + 1, x }, // down
        { y, x - 1 }, // left
        { y, x + 1 }, // right
    };

    // fight
    if (curr_state == 0) {
        rock(surr_state);
    } else if (curr_state == 1) {
        paper(surr_state);
    } else if (curr_state == 2) {
        scissor(surr_state);
    } else {
        throw std::invalid_argument("Error: Undefined Cell state");
    }
}

void update_game_arena()
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            game_logic(y, x);
        }
    }
}
