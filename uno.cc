#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "card.h"
#include "player.h"

namespace uno {

void InitializeSrand() {
  unsigned long a = clock();
  unsigned long b = time(nullptr);
  unsigned long c = getpid();

  srand(a + b + c);
}

int loop() {
  InitializeSrand();

  std::vector<std::unique_ptr<UnoPlayer>> players;
  players.push_back(std::unique_ptr<UnoPlayer>(new HumanUnoPlayer()));
  players.push_back(std::unique_ptr<UnoPlayer>(new ComputerUnoPlayer()));
  players.push_back(std::unique_ptr<UnoPlayer>(new ComputerUnoPlayer()));

  std::vector<Card> deck = BuildDeck();
  Shuffle(&deck);

  // Deal.
  std::vector<Card> hands[players.size()];
  for (int i = 0; i < 7; i++) {
    for (auto &hand : hands) {
      hand.push_back(deck.back());
      deck.pop_back();
    }
  }

  // Flip the first card over (keep going if it is black.).
  std::vector<Card> table;
  do {
    table.push_back(deck.back());
    deck.pop_back();
  } while (table.back().GetColor() == Card::Color::BLACK);

  int user_index = 0;
  int pick_up = 0;
  bool reverse = false;
  auto next_color = Card::Color::BLACK;  // Basically means ignore next_color.

  for (; true; user_index += (reverse ? -1 : 1)) {
    user_index = (user_index + players.size()) % players.size();
    int current_user_index = user_index;

    std::vector<Card> &user_hand = hands[user_index];

    // Reshuffle the table cards into the deck.
    if (deck.size() < 4) {
      deck.insert(deck.end(), table.begin(), table.end() - 1);
      table.erase(table.begin(), table.end() - 1);
      Shuffle(&deck);
    }

    // Previous player is forcing us to pick up cards.
    if (pick_up > 0) {
      std::cout << "Player " << user_index << " is picking up " << pick_up
                << " cards." << std::endl;
      user_hand.insert(user_hand.end(), deck.end() - pick_up, deck.end());
      deck.erase(deck.end() - pick_up, deck.end());
    }
    pick_up = 0;

    int card_index =
        players[user_index]->PickMove(table.back(), next_color, user_hand);
    if (card_index == -1) {
      std::cout << "Player " << user_index << " is picking up and now has "
                << user_hand.size() + 1 << " cards remaining." << std::endl;

      user_hand.push_back(deck.back());
      deck.pop_back();
      continue;
    }

    // TODO: Validate that it was a legal move...

    next_color = Card::Color::BLACK;  // Reset the next_color.

    {
      std::cout << "Player " << user_index << " is playing a "
                << user_hand[card_index].ToString() << " and has "
                << user_hand.size() - 1 << " cards remaining." << std::endl;

      if (user_hand[card_index].GetColor() == Card::Color::BLACK) {
        next_color = players[user_index]->PickColor();

        if (user_hand[card_index].GetType() == Card::Type::WILD_4) {
          pick_up = 4;
        }
      } else if (user_hand[card_index].GetType() == Card::Type::SKIP_TURN) {
        user_index += (reverse ? -1 : 1);
      } else if (user_hand[card_index].GetType() == Card::Type::REVERSE) {
        reverse = !reverse;
      } else if (user_hand[card_index].GetType() == Card::Type::PICK_UP_2) {
        pick_up = 2;
      }

      table.push_back(user_hand[card_index]);
      user_hand.erase(user_hand.begin() + card_index);
    }

    if (user_hand.size() == 0) {
      std::cout << "Player " << current_user_index << " has won." << std::endl;
      return 0;
    }
  }

  return 0;
}

}  // namespace uno {

int main() { return uno::loop(); }
