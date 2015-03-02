#include "card.h"

#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace uno {

namespace {

static const std::string INVALID("Invalid");

static const std::string RED{"Red"};
static const std::string BLUE{"Blue"};
static const std::string YELLOW("Yellow");
static const std::string GREEN{"Green"};
static const std::string BLACK{"Black"};

static const std::string ONE{"1"};
static const std::string TWO{"2"};
static const std::string THREE{"3"};
static const std::string FOUR{"4"};
static const std::string FIVE{"5"};
static const std::string SIX{"6"};
static const std::string SEVEN{"7"};
static const std::string EIGHT{"8"};
static const std::string NINE{"9"};
static const std::string ZERO{"0"};
static const std::string SKIP_TURN{"SkipTurn"};
static const std::string PICK_UP_2{"PickUp2"};
static const std::string REVERSE{"Reverse"};
static const std::string WILD{"WildCard"};
static const std::string WILD_4{"WildCard-4"};

}  // namespace {

const std::string &Card::ToString(Color color) {
#define COLOR_STR(x) \
  case Color::x:     \
    return (x)
  switch (color) {
    COLOR_STR(RED);
    COLOR_STR(BLUE);
    COLOR_STR(GREEN);
    COLOR_STR(YELLOW);
    COLOR_STR(BLACK);
  }
#undef COLOR_STR
  assert(false);
  return INVALID;
}

const std::string &Card::ToString(Type type) {
#define TYPE_STR(x) \
  case Type::x:     \
    return (x)
  switch (type) {
    TYPE_STR(ONE);
    TYPE_STR(TWO);
    TYPE_STR(THREE);
    TYPE_STR(FOUR);
    TYPE_STR(FIVE);
    TYPE_STR(SIX);
    TYPE_STR(SEVEN);
    TYPE_STR(EIGHT);
    TYPE_STR(NINE);
    TYPE_STR(ZERO);
    TYPE_STR(SKIP_TURN);
    TYPE_STR(PICK_UP_2);
    TYPE_STR(REVERSE);
    TYPE_STR(WILD);
    TYPE_STR(WILD_4);
  }
#undef TYPE_STR
  assert(false);
  return INVALID;
}

std::string Card::ToString() const {
  return ToString(this->color_) + "-" + ToString(this->type_);
}

void ShowCards(const std::vector<Card> &deck) {
  for (size_t i = 0; i < deck.size(); i++) {
    std::cout << i + 1 << ": " << deck[i].ToString() << std::endl;
  }
  std::cout << std::endl;
}

int myrandom(int i) { return rand() % i; }

void Shuffle(std::vector<Card> *deck) {
  random_shuffle(deck->begin(), deck->end(), myrandom);
}

std::vector<Card> BuildDeck() {
  std::vector<Card> deck;

  // An official UNO deck has 108 cards.
  for (auto &color : {Card::Color::RED,   Card::Color::BLUE,
                      Card::Color::GREEN, Card::Color::YELLOW}) {
    deck.push_back({color, Card::Type::ZERO});

    for (auto &type :
         {Card::Type::ONE,       Card::Type::TWO,       Card::Type::THREE,
          Card::Type::FOUR,      Card::Type::FIVE,      Card::Type::SIX,
          Card::Type::SEVEN,     Card::Type::EIGHT,     Card::Type::NINE,
          Card::Type::SKIP_TURN, Card::Type::PICK_UP_2, Card::Type::REVERSE}) {
      deck.push_back({color, type});
      deck.push_back({color, type});
    }
  }

  for (int i = 0; i < 4; i++) {
    deck.push_back({Card::Color::BLACK, Card::Type::WILD});
    deck.push_back({Card::Color::BLACK, Card::Type::WILD_4});
  }

  return deck;
}

}  // namespace uno {
