#ifndef Util_hpp
#define Util_hpp

#include <cstdint>
#include <bitset>
#include <array>
#include <tuple>
#include <experimental/optional>

namespace opt = std::experimental;

template<typename E>
constexpr auto ToUType(E e) noexcept { return static_cast<std::underlying_type_t<E>>(e); }

template<typename E>
constexpr auto NextUType(E e) noexcept { return ToUType(e) + 1; }

template <typename A, size_t size>
class FixedSet {
public:
  size_t Count() const { return mBitset.count(); }
  size_t Size() const { return size; }
  bool Get(A a) const { return mBitset[ToUType(a)]; }
  bool operator[](A a) const { return Get(a); }
  void Reset() { mBitset.reset(); }
  void Reset(A a) { mBitset.reset(ToUType(a)); }
  void Set() { mBitset.set(); } 
  void Set(A a) { mBitset.set(ToUType(a)); }
private:
  std::bitset<size> mBitset;
};

template <typename A, typename B, size_t size>
class Table {
public:
  Table() {}
  B& operator[](A a) { return mArray[ToUType(a)]; }
  size_t Size() const { return mArray.size(); }
private:
  std::array<B, size> mArray;
};

#endif
