#include <iostream>
template<class T>
class MyUnique {
    T * p;
public:
    explicit MyUnique(T *p = nullptr) : p(p) {}
    ~MyUnique() {
        delete p;
    }
    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;
    MyUnique(MyUnique&& other) noexcept : p(other.p) {
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
    T * get() const {
        return p;
    }
    T & operator*() {
        return *p;
    }
    T * operator->() {
        return p;
    }
};
template<typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args) {
    return MyUnique<T>(new T(std::forward<Args>(args)...));
}
class MyPoint {
    int x, y;
public:
    MyPoint(int x, int y) : x(x), y(y) {
        std::cout << "MyPoint(int x, int y): x=" << x << " y=" << y << std::endl;
    }
};
int main() {
    auto p1 = Make_MyUnique<MyPoint>(5, 10);
    std::cout << "Point: " << p1->x << ", " << p1->y << std::endl;
    MyUnique<MyPoint> p2 = std::move(p1);
    if (p1.get() == nullptr) {
        std::cout << "p1 is null after move" << std::endl;
    }
    std::cout << "Point: " << p2->x << ", " << p2->y << std::endl;
    return 0;
}
