#ifndef CARD_HPP
#define CARD_HPP
/* Card.hpp
 *
 * Represents a single playing card
 *
 * Original by Andrew DeOrio for EECS280 p3-euchre
 * awdeorio@umich.edu
 * 2014-12-21
 */

#include <iostream>

enum Rank {
  ZERO    = 0,
  ONE     = 1,
  TWO     = 2,
  THREE   = 3,
  FOUR    = 4,
  FIVE    = 5,
  SIX     = 6,
  SEVEN   = 7,
  EIGHT   = 8,
  SKIP    = 9,
  REVERSE = 10,
  PLUS2   = 11,
  PLUS4   = 12,
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank correspoinding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str);

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank);

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank);

// Represent a Card's suit
enum Suit {
  RED    = 0,
  YELLOW = 1,
  GREEN  = 2,
  BLUE   = 3,
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit correspoinding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str);

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit);

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit);


class Card {
public:

  //EFFECTS Initializes Card to the Two of Spades
  Card();

  //EFFECTS Initializes Card to specified rank and suit
  Card(Rank rank_in, Suit suit_in);

  //EFFECTS Returns the rank
  Rank get_rank() const;

  //EFFECTS Returns the suit.  Does not consider trump.
  Suit get_suit() const;


private:
  Rank rank;
  Suit suit;

  // This "friend declaration" allows the implementation of operator>>
  // to access private member variables of the Card class.
  friend std::istream & operator>>(std::istream &is, Card &card);
};

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card);

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card);

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump);

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump);

#endif // CARD_HPP
