#include <iostream>
template<class T>
class MyShared {
    T * p;
    int * ref_count;
public:
    explicit MyShared(T *p = nullptr) : p(p), ref_count(new int(1)) {}
    ~MyShared() {
        release();
    }
    MyShared(const MyShared& other) : p(other.p), ref_count(other.ref_count) {
        ++(*ref_count);
    }
    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            release();
            p = other.p;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }
    MyShared(MyShared&& other) noexcept : p(other.p), ref_count(other.ref_count) {
        other.p = nullptr;
        other.ref_count = nullptr;
    }
    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            release();
            p = other.p;
            ref_count = other.ref_count;
            other.p = nullptr;
            other.ref_count = nullptr;
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
private:
    void release() {
        if (ref_count) {
            --(*ref_count);
            if (*ref_count == 0) {
                delete p;
                delete ref_count;
            }
        }
    }
};
template<typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(std::forward<Args>(args)...));
}
int main() {
    auto p1 = Make_MyShared<MyPoint>(5, 10);
    std::cout << "Point: " << p1->x << ", " << p1->y << std::endl;
    MyShared<MyPoint> p2 = p1;
    std::cout << "Point after copy: " << p2->x << ", " << p2->y << std::endl;
    return 0;
}
