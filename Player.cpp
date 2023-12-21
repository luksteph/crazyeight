#include "Player.hpp"
#include "Card.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>

class SimplePlayer : public Player {
    private:
    std::string name;
    std::vector<Card> hand;

    public:
    SimplePlayer(const std::string &name_in) : name(name_in){}

    const std::string & get_name() const override;

    void add_card(const Card &c) override;

    Card play_card(const Card & upcard) override;
    
    bool hand_empty() const override;
};

const std::string & SimplePlayer::get_name() const {
    return name;
}

void SimplePlayer::add_card(const Card &c) {
    hand.push_back(c);
}

Card SimplePlayer::play_card(const Card & upcard) {

}

bool SimplePlayer::hand_empty() const {
    return hand.empty();
}


class HumanPlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;

public:
    HumanPlayer(const std::string &name_in) : name(name_in){}

    const std::string & get_name() const override;

    void add_card(const Card &c) override;

    Card play_card(const Card & upcard) override;

    bool hand_empty() const override;

    void print_hand() const;
};

const std::string & HumanPlayer::get_name() const {
    return name;
}

void HumanPlayer::add_card(const Card &c) {
    hand.push_back(c);
    std::sort(hand.begin(), hand.end());
}

Card HumanPlayer::play_card(const Card & upcard) {
    int card_index(0); Card *chosen_one;
    print_hand();
    std::cout << "Human player " << name << ", please select a card:\n";
    std::cin >> card_index;
    chosen_one = &hand[card_index];
    hand.erase(hand.begin() + card_index);
    return *chosen_one;
}

bool HumanPlayer::hand_empty() const {
    return hand.empty();
}

void HumanPlayer::print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    std::cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Simple") {
    return new SimplePlayer(name);
  }
  else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}