#include "RedBlue.hpp"

namespace RedBlue {

std::ostream& operator<<(std::ostream& os, NonVolStatus::Tag nvs) {
  switch (nvs) {
  case NonVolStatus::Burn: os << "Burn"; break;
  case NonVolStatus::Freeze: os << "Freeze"; break;
  case NonVolStatus::Paralysis: os << "Paralysis"; break;
  case NonVolStatus::Poison: os << "Poison"; break;
  case NonVolStatus::None: os << "None"; break;
  case NonVolStatus::Sleep: os << "Sleep"; break;
  case NonVolStatus::Toxic: os << "Toxic"; break;
  }
}

}
