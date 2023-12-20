#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

constexpr const char *const RANK_NAMES[] = {
  "Zero",   // ZERO
  "One",   // ONE
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Skip",  // SKIP
  "Reverse",   // REVERSE
  "+2",  // PLUS2
  "+4", // PLUS4
};

//REQUIRES str represents a valid rank ("Zero", "One", ..., "Plus4")
Rank string_to_rank(const std::string &str) {
  for(int r = ZERO; r <= PLUS4; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = RED; s <= BLUE; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}

//EFFECTS Initializes Card to the Two of Spades
  Card::Card() {
    rank = ZERO;
    suit = RED;
  }

  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(Rank rank_in, Suit suit_in) {
    rank = rank_in;
    suit = suit_in;
  }

  //EFFECTS Returns the rank
  Rank Card::get_rank() const {
    return rank;
  }

  //EFFECTS Returns the suit.  Does not consider trump.
  Suit Card::get_suit() const {
    return suit;
  }

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
  operator<<(os, card.get_rank());
  os << " of ";
  operator<<(os, card.get_suit());
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card) {
  std::string ignore;
  operator>>(is, card.rank);
  is >> ignore;
  operator>>(is, card.suit);
  return is;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() < rhs.get_rank()) return true;
  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() < rhs.get_suit()) return true;
  }
  return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() <= rhs.get_rank()) return true;
  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() <= rhs.get_suit()) return true;
  }
  return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() > rhs.get_rank()) return true;
  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() > rhs.get_suit()) return true;
  }
  return false;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() >= rhs.get_rank()) return true;
  else if (lhs.get_rank() == rhs.get_rank()) {
    if (lhs.get_suit() >= rhs.get_suit()) return true;
  }
  return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() == rhs.get_rank()) {
    return (lhs.get_suit() == rhs.get_suit());
  }
  return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    return (lhs.get_rank() != rhs.get_rank() 
        || lhs.get_suit() != rhs.get_suit());
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
  
}


