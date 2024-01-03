#include "Pack.hpp"
#include <cassert>
#include <vector>
#include <iostream>
// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
Pack::Pack() {
    next = 0;
    int iterator = 0;
    for (int s = RED; s <= BLUE; ++s) {
        Suit suit = static_cast<Suit>(s);
        for (int r = ZERO; r <= PLUS4; ++r) {
            Rank rank = static_cast<Rank>(r);
            Card c(rank, suit);
            cards.at(iterator) = c;
            ++iterator;
        }
    }
}

  // REQUIRES: pack_input contains a valid representation of a Pack
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    int iterator = 0;
    while (iterator < 52) {
        Card c;
        operator>>(pack_input, c);
        cards.at(iterator) = c;
        ++iterator;
    }
}

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    Card c = cards[next];
    next++;
    return c;
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    reset();
    int shuffle_count(0);
    std::array<Card, (PACK_SIZE/2)> first_half;
    std::array<Card, (PACK_SIZE/2)> second_half;
    while (shuffle_count < 7) {
        for (int i(0); i < 12; ++i) { // fix me
            first_half.at(i) = cards.at(i);
        }
        for (int i(12); i < 24; ++i) { // fix me
            second_half.at(i-12) = cards.at(i);
        }
        for (int i(0); i < 12; ++i) { // fix me
            cards.at(2*i) = second_half.at(i);
            cards.at(1+(2*i)) = first_half.at(i);
        }
        ++shuffle_count;
    }
}

  // EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    return (next >= 54);
}