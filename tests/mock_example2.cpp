#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Dependency
{
public:
    virtual ~Dependency() = default;
    virtual void DoSomething() = 0;
    virtual void DoAnotherThing() = 0;
};

class MockDependency : public Dependency
{
public:
    MOCK_METHOD(void, DoSomething, (), (override));
    MOCK_METHOD(void, DoAnotherThing, (), (override));
};

class ClassUnderTest
{
public:
    ClassUnderTest(Dependency &dependency) : dependency_(dependency) {}

    void PerformActions()
    {
        dependency_.DoSomething();
        dependency_.DoAnotherThing();
    }

private:
    Dependency &dependency_;
};

using ::testing::NaggyMock;
using ::testing::NiceMock;
using ::testing::StrictMock;

TEST(GMockExample, MockClassBehaviors)
{
    // NaggyMock Example
    {
        NaggyMock<MockDependency> naggy_mock;
        ClassUnderTest obj(naggy_mock);
        EXPECT_CALL(naggy_mock, DoSomething());

        obj.PerformActions(); // This will generate a warning for DoAnotherThing()
    }
    std::cout << "Hello 1" << std::endl;
    // NiceMock Example
    {
        NiceMock<MockDependency> nice_mock;
        ClassUnderTest obj(nice_mock);
        EXPECT_CALL(nice_mock, DoSomething());

        obj.PerformActions(); // This will NOT generate a warning for DoAnotherThing()
    }
    std::cout << "Hello 2" << std::endl;
    // StrictMock Example
    {
        StrictMock<MockDependency> strict_mock;
        ClassUnderTest obj(strict_mock);
        EXPECT_CALL(strict_mock, DoSomething());

        obj.PerformActions(); // This will cause the test to fail for DoAnotherThing()
    }
}