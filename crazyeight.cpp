#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
using namespace std;

void verify_input(int argc, char* argv[]);

class Game {
public:
    Game(char* arguments[], istream& pack_in);
    void play();
private:
    vector<Player*> players;
    Pack pack;
    bool do_shuffle;

    void deal();
    void play_hand();
    void play_round();
    void cleanup(); 
};

int main(int argc, char *argv[]) {
    verify_input(argc, argv);

    string pack_filename = argv[1];
    ifstream pack_in(pack_filename);
    
    if (!pack_in) {
        cout << "Error opening " << pack_filename << endl;
        exit(1);
    }

    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    Game game(argv, pack_in);
    
    game.play();
    pack_in.close();
}

void verify_input(int argc, char* argv[]) {
    if (argc != 11 || 
        atoi(argv[3]) > 100 || atoi(argv[3]) < 1 || 
        (strcmp(argv[2], "shuffle") && strcmp(argv[2], "noshuffle")) || 
        (strcmp(argv[5], "Simple") && strcmp(argv[5], "Human")) ||
        (strcmp(argv[7], "Simple") && strcmp(argv[7], "Human")) ||
        (strcmp(argv[9], "Simple") && strcmp(argv[9], "Human")) ||
        (strcmp(argv[11], "Simple") && strcmp(argv[11], "Human"))
        ) {
    cout << "Usage: crazyeight.exe PACK_FILENAME [shuffle|noshuffle] "
     << " NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     exit(1);
  }
}

Game::Game(char* arguments[], istream& pack_in) { 
    Pack pack(pack_in);
    
    if (strcmp(arguments[2], "shuffle") == 0) do_shuffle = true;
    else do_shuffle = false;

    for (int i = 0; i < 4; ++i) {
        players.push_back(Player_factory(
            arguments[(2 * i + 4)], arguments[(2 * i + 5)]));
    }

}

void Game::play() {
    // Run hands until winning score is reached
    
    // delete player objects
    cleanup();
}

void Game::play_hand() {
    
}

void Game::play_round() {
    
}

// MODIFIES player hands
// EFFECTS deals the cards, one to each player until everyone has 7
void Game::deal() {
    // setup

    // impl

    
}



// MODIFIES player vector, all of them get deleted
// EFFECTS deletes players
void Game::cleanup() {
    for (auto p : players) {
        delete p;
    }
}