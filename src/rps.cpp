#include "rps.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <time.h>
#include <vector>

#define HEIGHT 60
#define WIDTH 120

/// global data
const std::string symbol = "■";
int ground[HEIGHT][WIDTH] = { 0 };
long long rock_count = 0;
long long paper_count = 0;
long long scissor_count = 0;

/// function prototypes
void generate_battleground();
void print_color(int data);
void display_arena();
void rock(int surr_state[4][2]);
void paper(int surr_state[4][2]);
void scissor(int surr_state[4][2]);
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
    long long total = WIDTH * HEIGHT;
    while (paper_count != total && scissor_count != total && rock_count != total) {

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
// 2 --> Scissor ==> BOLDRED
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
    system("clear");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            print_color(ground[y][x]);
        }
        std::cout << '\n';
    }
}

// identifier for rock is 0
// rock beats scissor
void rock(int surr_state[4][2])
{
    for (int i = 0; i < 4; i++) {
        if (surr_state[i][0] < 0 || surr_state[i][1] < 0
            || surr_state[i][0] >= HEIGHT || surr_state[i][1] >= WIDTH) {
            continue;
        } else {
            if (ground[surr_state[i][0]][surr_state[i][1]] == 2) {
                ground[surr_state[i][0]][surr_state[i][1]] = 0;
                scissor_count++;
                paper_count--;
            }
        }
    }
}

// identifier for paper is 1
// paper beats rock
void paper(int surr_state[4][2])
{
    for (int i = 0; i < 4; i++) {
        if (surr_state[i][0] < 0 || surr_state[i][1] < 0
            || surr_state[i][0] >= HEIGHT || surr_state[i][1] >= WIDTH) {
            continue;
        } else {
            if (ground[surr_state[i][0]][surr_state[i][1]] == 0) {
                ground[surr_state[i][0]][surr_state[i][1]] = 1;
                scissor_count++;
                paper_count--;
            }
        }
    }
}

// identifier for scissor is 2
// scissor beats paper
void scissor(int surr_state[4][2])
{
    for (int i = 0; i < 4; i++) {
        if (surr_state[i][0] < 0 || surr_state[i][1] < 0
            || surr_state[i][0] >= HEIGHT || surr_state[i][1] >= WIDTH) {
            continue;
        } else {
            if (ground[surr_state[i][0]][surr_state[i][1]] == 1) {
                ground[surr_state[i][0]][surr_state[i][1]] = 2;
                scissor_count++;
                paper_count--;
            }
        }
    }
}

// the RPS game logic
void game_logic(int y, int x)
{
    // store current state
    int curr_state = ground[y][x];
    // store surrounding states
    int surr_state[4][2] = {
        { y - 1, x },
        { y + 1, x },
        { y, x - 1 },
        { y, x + 1 }
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
