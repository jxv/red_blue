#ifndef Util_h
#define Util_h

#include <cstdint>
#include <bitset>
#include <array>
#include <tuple>

template<typename E>
constexpr auto ToUType(E e) noexcept { return static_cast<std::underlying_type_t<E>>(e); }

template<typename E>
constexpr auto ToNextUType(E e) noexcept { return 1 + ToUType(e); }

template <typename A, size_t size>
class FixedSet {
public:
  void Reset() { bitset.reset(); }
  void Reset(A a) { bitset.reset(ToUType(a)); }
  void Set() { bitset.set(); } 
  void Set(A a) { bitset.set(ToUType(a)); }

  size_t GetCount() const { return bitset.count(); }
  size_t GetSize() const { return size; }
  bool Get(A a) const { return bitset[ToUType(a)]; }
  bool operator[](A a) const { return get(a); }

private:
  std::bitset<size> bitset;
};

template <typename A, size_t capacity>
class FixedVector {
public:
  FixedVector() : size(0) {}

  void PushBack(A a) {
    assert(size < capacity);
    array[size] = a;
    ++size;
  }
  void PopBack() {
    assert(size > 0);
    --size;
  }

  A& Get(size_t idx) const {
    assert(idx >= 0 && idx < size);
    return array[idx];
  }
  A& operator[](size_t idx) const { return Get(idx); }
  A& GetFront() const { 
    assert(size > 0);
    return array[0];
  }
  A& GetBack() const { 
    assert(size > 0);
    return array[size - 1];
  }

  size_t GetCapacity() const { return capacity; }
  size_t GetSize() const { return size; }
  bool IsEmpty() const { return size == 0; }

private:
  size_t size;
  std::array<A, capacity> array;
};

template <typename A, size_t capacity>
class FixedDeque {
public:
  FixedDeque() : head(0), size(0) {}

  void PushFront(A a) {
    assert(size < capacity);
    array[head - 1] = a;
    --head;
    ++size;
  }
  void PopFront() {
    assert(size > 0);
    ++head;
    --size;
  }

  void PushBack(A a) {
    assert(size < capacity);
    array[(head + size) % capacity] = a;
    ++size;
  }
  void PopBack() {
    assert(size > 0);
    --size;
  }

  A& Get(size_t idx) const {
    assert(idx >= 0 && idx < size);
    return array[(head + idx) % capacity];
  }
  A& operator[](size_t idx) const { return Get(idx); }
  A& GetFront() const { 
    assert(size > 0);
    return array[head];
  }
  A& GetBack() const { 
    assert(size > 0);
    return array[(head + size + capacity - 1) % capacity];
  }

  size_t GetCapacity() const { return capacity; }
  size_t GetSize() const { return size; }
  bool IsEmpty() const { return size == 0; }

private:
  size_t head;
  size_t size;
  std::array<A, capacity> array;
};

template <typename A, size_t capacity>
class FixedStack {
public:
  FixedStack() {}

  void PushBack(A a) { v.PushBack(a); }
  void PopBack() { v.PopBack(); }

  A& Get(size_t idx) const { return v[idx]; }
  A& operator[](size_t idx) const { return v[idx]; }
  A& GetBack() const { return v.GetBack(); }

  size_t GetCapacity() const { return capacity; }
  size_t GetSize() const { return v.GetSize(); }

private:
  FixedVector<A, capacity> v;
};

template <typename A, size_t capacity>
class FixedQueue {
public:
  FixedQueue() {}

  void PushBack(A a) { v.PushBack(a); }
  void PopBack() { v.PopBack(); }

  A& Get(size_t idx) const { return v[idx]; }
  A& operator[](size_t idx) const { return v[idx]; }
  A& GetFront() const { return v.GetFront(); }
  A& GetBack() const { return v.GetBack(); }

  size_t GetCapacity() const { return capacity; }
  size_t GetSize() const { return v.GetSize(); }

private:
  FixedVector<A, capacity> v;
};

#endif
