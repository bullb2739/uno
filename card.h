#ifndef __final__subroutines__
#define __final__subroutines__

#include <string>
#include <vector>

namespace uno {

class Card final {
 public:
  enum class Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BLACK,
  };
  static const std::string& ToString(Color color);

  enum class Type {
    // These are standard colors.
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    ZERO,
    SKIP_TURN,
    PICK_UP_2,
    REVERSE,

    // These are black.
    WILD,
    WILD_4,
  };
  static const std::string& ToString(Type type);

  Card(Color color, Type type) : color_{color}, type_{type} {}

  Color GetColor() const { return color_; }
  Type GetType() const { return type_; }

  std::string ToString() const;

 private:
  Color color_;
  Type type_;
};

void ShowCards(const std::vector<Card>& deck);
void Shuffle(std::vector<Card>* deck);
std::vector<Card> BuildDeck();

}  // namespace uno {

#endif /* defined(__final__subroutines__) */
