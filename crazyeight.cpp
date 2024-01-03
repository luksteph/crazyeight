#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <queue>
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
    queue<Card> stack;
    Pack pack;
    bool do_shuffle;
    bool play_clockwise;
    Card *top_card;
    class outOfCardsException{};

    void deal();
    void play_hand();
    void play_round(Player *current_player);
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
    
    char a = 'Y';
    while (a == 'Y' || a =='y') {
        game.play();
        cout << "Would you like to play a new game? [Y/N]: ";
        cin >> a;
    }
    
    cout << "Thanks for playing!";
    pack_in.close();
}

void verify_input(int argc, char* argv[]) {
    if (argc != 11 || 
        (strcmp(argv[2], "shuffle") && strcmp(argv[2], "noshuffle")) || 
        (strcmp(argv[4], "Simple") && strcmp(argv[4], "Human")) ||
        (strcmp(argv[6], "Simple") && strcmp(argv[6], "Human")) ||
        (strcmp(argv[8], "Simple") && strcmp(argv[8], "Human")) ||
        (strcmp(argv[10], "Simple") && strcmp(argv[10], "Human"))
        ) {
    cout << "Usage: ./crazyeight.exe PACK_FILENAME [shuffle|noshuffle]"
     << " NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     exit(1);
  }
}

Game::Game(char* arguments[], istream& pack_in) { 
    Pack pack(pack_in); play_clockwise = true;
    
    if (strcmp(arguments[2], "shuffle") == 0) do_shuffle = true;
    else do_shuffle = false;

    for (int i = 0; i < 4; ++i) {
        players.push_back(Player_factory(
            arguments[(2 * i + 3)], arguments[(2 * i + 4)]));
    }

}

void Game::play() {
    // Deal cards
    deal();

    bool still_going = true;
    int cards_played(0), current_p_index = 0;

    while (still_going) {
        try {
            play_round(players[current_p_index]);
            if (play_clockwise) current_p_index = (current_p_index + 1) % 4;
            else current_p_index = (current_p_index - 1) % 4; // will break on reverse
        }
        catch (outOfCardsException &e) {
            still_going = false;
        }
        cards_played++;
    }

    // delete player objects
    cleanup();
}

void Game::play_round(Player *p) { // rename to reflect player turn
    auto tc_temp = p->play_card(*top_card);
    top_card = &tc_temp;
    cout << *top_card << " played!" << endl;
    if (p->hand_empty()) throw new outOfCardsException;
}

void Game::play_hand() {
    
}

// MODIFIES player hands, card "stack"
// EFFECTS deals the cards, one to each player until everyone has 7
void Game::deal() {
    for (size_t i = 0; i <=7; ++i) {
        for (auto p : players) p->add_card(pack.deal_one());
    }
    auto tc_temp = pack.deal_one();
    top_card = &tc_temp;
    while (!pack.empty()) {
        stack.push(pack.deal_one());
    }

}

// MODIFIES player vector, all of them get deleted
// EFFECTS deletes players
void Game::cleanup() {
    for (auto p : players) {
        delete p;
    }
}