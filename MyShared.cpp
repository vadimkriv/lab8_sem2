
#include <iostream>

template <typename T>
class MyShared {
public:
  std::shared_ptr<T> p;

  MyShared(T* ptr) : p(std::make_shared<T>(*ptr)) {}
  ~MyShared() = default;

  T* get() const { return p.get(); }
  T& operator*() { return *p; }
  T* operator->() { return p.get(); }

  MyShared(MyShared&& other) noexcept {
    p = std::move(other.p);
  }
  MyShared& operator=(MyShared&& other) noexcept {
    if (this != &other) {
      p = std::move(other.p);
    }
    return *this;
  }
};

template <typename T>
MyShared<T> Make_MyShared(T* ptr) {
  return MyShared<T>(ptr);
}

int main() {
  class MyPoint {
  public:
    int x, y;

    MyPoint(int x_, int y_) : x(x_), y(y_) {}
  };
  MyShared<MyPoint> ptr = Make_MyShared(new MyPoint(5, 10));
  std::cout << ptr->x << " " << ptr->y << std::endl;
  (*ptr).x = 15;
  std::cout << ptr->x << " " << ptr->y << std::endl;
  MyShared<MyPoint> ptr2 = std::move(ptr);
  std::cout << ptr2->x << " " << ptr2->y << std::endl;
  return 0;
}
