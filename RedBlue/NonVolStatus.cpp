#include "RedBlue.hpp"

namespace RedBlue {

std::ostream& operator<<(std::ostream& os, NonVolStatus::Tag nvs) {
  switch (nvs) {
  case NonVolStatus::burn: os << "Burn"; break;
  case NonVolStatus::freeze: os << "Freeze"; break;
  case NonVolStatus::paralysis: os << "Paralysis"; break;
  case NonVolStatus::poison: os << "Poison"; break;
  case NonVolStatus::none: os << "None"; break;
  case NonVolStatus::sleep: os << "Sleep"; break;
  case NonVolStatus::toxic: os << "Toxic"; break;
  }
}

}
