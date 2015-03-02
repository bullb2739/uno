#include "player.h"

#include <iostream>

namespace uno {

int HumanUnoPlayer::PickMove(const Card &top_card,
                             const Card::Color &expected_color,
                             const std::vector<Card> &users_hand) const {
  int uin;
  while (true) {
    std::cout << std::endl;
    std::cout << "The top card on the table is a " << top_card.ToString()
              << std::endl;
    if (top_card.GetColor() == Card::Color::BLACK) {
      std::cout << "The chosen color was: " << Card::ToString(expected_color)
                << std::endl;
    }

    std::cout << "Select a Card to play, or press 0 to pick up" << std::endl;
    ShowCards(users_hand);

    std::cin >> uin;

    if (uin < 0 || uin > (int)users_hand.size()) {
      std::cout << std::endl << "That is not a valid entry, try again"
                << std::endl;
      continue;
    }

    uin--;
    if (uin == -1) {
      break;
    } else if (users_hand[uin].GetColor() == Card::Color::BLACK) {
      break;
    } else if (top_card.GetColor() == users_hand[uin].GetColor() ||
               top_card.GetType() == users_hand[uin].GetType() ||
               expected_color == users_hand[uin].GetColor()) {
      break;
    } else {
      std::cout << "That card is an invalid choice, please try again"
                << std::endl;
    }
  }
  return uin;
}

Card::Color HumanUnoPlayer::PickColor() const {
  Card::Color colours[] = {Card::Color::RED,   Card::Color::BLUE,
                           Card::Color::GREEN, Card::Color::YELLOW};
  while (true) {
    std::cout << "please select the color you wish to change to" << std::endl;
    for (int n = 0; n < 4; n++) {
      std::cout << n << ": " << Card::ToString(colours[n]) << std::endl;
    }

    int color;
    std::cin >> color;
    if (color < 0 || color > 3) {
      std::cout << "That is not a valid choice" << std::endl;
    } else {
      return colours[color];
    }
  }
}

int ComputerUnoPlayer::PickMove(const Card &top_card,
                                const Card::Color &expected_color,
                                const std::vector<Card> &users_hand) const {
  int uin;
  for (uin = 0; uin < (int)users_hand.size(); uin++) {
    if (users_hand[uin].GetColor() == Card::Color::BLACK) {
      return uin;
    } else if (top_card.GetColor() == users_hand[uin].GetColor() ||
               top_card.GetType() == users_hand[uin].GetType() ||
               expected_color == users_hand[uin].GetColor()) {
      return uin;
    }
  }
  return -1;
}

Card::Color ComputerUnoPlayer::PickColor() const { return Card::Color::RED; }

}  // namespace uno {
