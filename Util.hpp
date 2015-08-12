#ifndef Util_hpp
#define Util_hpp

#include <cstdint>
#include <bitset>
#include <array>
#include <tuple>
#include <experimental/optional>

namespace opt = std::experimental;

template<typename E>
constexpr auto to_utype(E e) noexcept { return static_cast<std::underlying_type_t<E>>(e); }

template<typename E>
constexpr auto to_next_utype(E e) noexcept { return to_utype(e) + 1; }

template <typename A, size_t size>
class FixedSet {
public:
  size_t get_count() const { return bitset.count(); }
  size_t get_size() const { return size; }
  bool get(A a) const { return bitset[to_utype(a)]; }
  bool operator[](A a) const { return Get(a); }
  void reset() { bitset.reset(); }
  void reset(A a) { bitset.reset(to_utype(a)); }
  void set() { bitset.set(); } 
  void set(A a) { bitset.set(to_utype(a)); }
private:
  std::bitset<size> bitset;
};

template <typename A, typename B, size_t size>
class Table {
public:
  Table() {}
  B& operator[](A a) { return array[to_utype(a)]; }
  size_t get_size() const { return size; }
private:
  std::array<B, size> array;
};

#endif
