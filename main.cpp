#include "iostream"

template<class T>
class Base : public std::enable_shared_from_this<T> {
public:
    Base() {
        std::cout << "Base() called" << std::endl;
    }

    Base(int fuckYou) {
        std::cout << "Base(int fuckYou) called" << std::endl;
        m_fuckYou = fuckYou;
    }

private:
    int m_fuckYou;
};

template<class T>
class Derived : public Base<T> {
public:
    Derived() {
        std::cout << "Derived() called" << std::endl;
    }

    Derived(int fuckYou) : Base<T>(fuckYou) {
        std::cout << "Derived(int fuckYou) called" << std::endl;
    }
};

class TestClass : public Derived<TestClass> {
    using Derived::Derived;
};

int main() {
    TestClass huso;
    TestClass huso2(2);
    return 0;
}
