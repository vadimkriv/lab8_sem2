#include <iostream>

template <typename T>
class MyUnique {
public:
  T* p = nullptr;

  MyUnique(T* ptr) : p(ptr) {}
  ~MyUnique() { delete p; }

  T* get() const { return p; }
  T& operator*() { return *p; }
  T* operator->() { return p; }

  MyUnique(MyUnique&& other) noexcept {
    p = other.p;
    other.p = nullptr;
  }
  MyUnique& operator=(MyUnique&& other) noexcept {
    if (this != &other) {
      delete p;
      p = other.p;
      other.p = nullptr;
    }
    return *this;
  }
};

// Функция Make_MyUnique
template <typename T>
MyUnique<T> Make_MyUnique(T* ptr) {
  return MyUnique<T>(ptr);
}

// Пример использования в main
int main() {
  class MyPoint {
  public:
    int x, y;

    MyPoint(int x_, int y_) : x(x_), y(y_) {}
  };

  MyUnique<MyPoint> ptr = Make_MyUnique(new MyPoint(5, 10));

  std::cout << ptr->x << " " << ptr->y << std::endl;
  (*ptr).x = 15;
  std::cout << ptr->x << " " << ptr->y << std::endl;

  return 0;
}
