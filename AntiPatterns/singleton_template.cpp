#include <memory>
#include <iostream>

template<typename T>
class Singleton {
public:
    static T& instance();

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    struct token {};
    Singleton() {}
};


template<typename T>
T& Singleton<T>::instance()
{
    static const std::unique_ptr<T> instance{
        new T{token{}}
    };
    return *instance;
}


class Test final : public Singleton<Test>
{
public:
    Test(token) { std::cout << "constructed" << std::endl; }
    ~Test() {  std::cout << "destructed" << std::endl; }

    void use() const { std::cout << "in use" << std::endl; };
};

int main()
{
    // Test t; /* cannot be created */

    std::cout << "Entering main()" << std::endl;
    {
        auto const& t = Test::instance();
        t.use();
    }
    {
        auto const& t = Test::instance();
        t.use();
    }
    std::cout << "Leaving main()" << std::endl;
}
