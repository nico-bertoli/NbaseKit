#include <gtest/gtest.h>
#include <NbaseKit/Singleton.h>
#include <vector>
#include <string>
#include <type_traits>

template<typename T>
using Singleton = NbaseKit::Singleton<T>;

//-------------------------------------------------------- classes

class SingletonInt : public Singleton<SingletonInt>
{
    friend class Singleton<SingletonInt>;

private:
    SingletonInt() = default;
    ~SingletonInt() = default;

public:
    int value = 0;
    void SetValue(int v) { value = v; }
    int GetValue() const { return value; }
};

class SingletonString : public Singleton<SingletonString>
{
    friend class Singleton<SingletonString>;

private:
    SingletonString() = default;
    ~SingletonString() = default;

public:
    std::string name;
    void SetName(const std::string& n) { name = n; }
    const std::string& GetName() const { return name; }
};

//-------------------------------------------------------- test class

class SingletonTest : public ::testing::Test
{
protected:
    //automatically called before each test case
    void SetUp() override
    {
        // Reset the singleton state if needed
        SingletonInt::Instance().SetValue(0);
        SingletonString::Instance().SetName("");
    }
};

//-------------------------------------------------------- tests

TEST_F(SingletonTest, CopyPrevented)
{
    static_assert(!std::is_copy_constructible_v<SingletonInt>, 
                  "SingletonInt should not be copy constructible");
    
    static_assert(!std::is_copy_assignable_v<SingletonInt>, 
                  "SingletonInt should not be copy assignable");
    
    static_assert(!std::is_move_constructible_v<SingletonInt>, 
                  "SingletonInt should not be move constructible");
    
    static_assert(!std::is_move_assignable_v<SingletonInt>, 
                  "SingletonInt should not be move assignable");
}

TEST_F(SingletonTest, InstantiationPrevented)
{
    static_assert(!std::is_default_constructible_v<SingletonInt>, 
                  "SingletonInt should not be directly constructible");
    
    static_assert(!std::is_default_constructible_v<SingletonString>, 
                  "SingletonString should not be directly constructible");
}

TEST_F(SingletonTest, SameInstanceReturned)
{
    SingletonInt& instance1 = SingletonInt::Instance();
    SingletonInt& instance2 = SingletonInt::Instance();
    SingletonInt& instance3 = SingletonInt::Instance();

    EXPECT_EQ(&instance1, &instance2);
    EXPECT_EQ(&instance2, &instance3);
    EXPECT_EQ(&instance1, &instance3);
}

TEST_F(SingletonTest, InstancePersistsState)
{
    SingletonInt& instance1 = SingletonInt::Instance();
    instance1.SetValue(42);

    SingletonInt& instance2 = SingletonInt::Instance();
    EXPECT_EQ(instance2.GetValue(), 42);
    EXPECT_EQ(instance1.GetValue(), 42);

    instance2.SetValue(100);
    SingletonInt& instance3 = SingletonInt::Instance();
    EXPECT_EQ(instance3.GetValue(), 100);
    EXPECT_EQ(instance1.GetValue(), 100);
    EXPECT_EQ(instance2.GetValue(), 100);
}

TEST_F(SingletonTest, WorksAcrossScopes)
{
    constexpr int kValueSet = 99;
    SingletonInt* instance1Ptr = nullptr;
    {
        SingletonInt& instance1 = SingletonInt::Instance();
        instance1Ptr = &instance1;
        instance1.SetValue(kValueSet);
    }

    {
        SingletonInt& instance2 = SingletonInt::Instance();
        EXPECT_EQ(instance2.GetValue(), kValueSet);
        EXPECT_EQ(instance1Ptr, &instance2); // Same instance reference
    }
}