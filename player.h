#ifndef __final__player__
#define __final__player__

#include <string>
#include <vector>

#include "card.h"

namespace uno {

class UnoPlayer {
 public:
  virtual int PickMove(const Card &top_card, const Card::Color &expected_color,
                       const std::vector<Card> &users_hand) const = 0;
  virtual Card::Color PickColor() const = 0;
};

class HumanUnoPlayer : public UnoPlayer {
 public:
  int PickMove(const Card &top_card, const Card::Color &expected_color,
               const std::vector<Card> &users_hand) const override;
  Card::Color PickColor() const override;
};

class ComputerUnoPlayer : public UnoPlayer {
 public:
  int PickMove(const Card &top_card, const Card::Color &expected_color,
               const std::vector<Card> &users_hand) const override;
  Card::Color PickColor() const override;
};

}  // namespace uno {

#endif
