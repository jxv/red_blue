#include "RedBlue.h"

namespace RedBlue {

PowerPoints::PowerPoints()
: current(0)
, maximum(0)
, stage(PowerPointStage::Zero) {}

PowerPoints::PowerPoints(Move move) 
: stage(PowerPointStage::Zero) {
  current = 10;
  maximum = 10;
}

int PowerPoints::GetCurrent() const {
  return current;
}

int PowerPoints::GetMaximum() const {
  return maximum;
}

PowerPointStage PowerPoints::GetStage() const {
  return stage;
}

void PowerPoints::Use() {
  assert(current > 0);
  --current;
}

void PowerPoints::RestoreFull() {
  current = maximum;
}

void PowerPoints::Restore(int points) {
  assert(current > 0);
  current = std::min(current + points, maximum);
}

void PowerPoints::IncrementStage() {
  switch (stage) {
  case PowerPointStage::Zero: stage = PowerPointStage::One; break;
  case PowerPointStage::One: stage = PowerPointStage::Two; break;
  case PowerPointStage::Two: stage = PowerPointStage::Three; break;
  case PowerPointStage::Three: stage = PowerPointStage::Four; break;
  case PowerPointStage::Four: stage = PowerPointStage::Five; break;
  case PowerPointStage::Five: stage = PowerPointStage::Six; break;
  case PowerPointStage::Six: assert(false);
  }
  //TODO: increase current and maximum
}

std::ostream& operator<<(std::ostream& os, PowerPointStage stage) {
  switch (stage) {
  case PowerPointStage::Zero: os << "Zero"; break;
  case PowerPointStage::One: os << "One"; break;
  case PowerPointStage::Two: os << "Two"; break;
  case PowerPointStage::Three: os << "Three"; break;
  case PowerPointStage::Four: os << "Four"; break;
  case PowerPointStage::Five: os << "Five"; break;
  case PowerPointStage::Six: os << "Six"; break;
  }
}

}
