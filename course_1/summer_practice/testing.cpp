#include <gtest/gtest.h>
#include <string>
#include "scope_guard.h"

// Todo как сделать без копипаста, но с другой стороны это ведь unit-testы там не нужная сложная логика

enum class TestEvent : unsigned char {
  NOTHING,
  EVENT
};

enum class TestException : unsigned char {
  ThrowException,
  NoThrowException
};

void TestOnSuccess(TestException testExceptionType, TestEvent * event) {
  auto ScopeGuardOnSuccess = SG::setScopeGuardOnSuccess([&event]{
    *event = TestEvent::EVENT;
  });
  if (testExceptionType == TestException::ThrowException) {
    throw std::out_of_range("test_exception");
  }
}

TEST(ScopeGuardOnSuccessTests, TestOnSuccessNoexcept) {
  TestEvent event = TestEvent::NOTHING;
  EXPECT_NO_THROW(TestOnSuccess(TestException::NoThrowException, &event));
  EXPECT_EQ(event, TestEvent::EVENT);
}

TEST(ScopeGuardOnSuccessTests, TestOnSuccessExcept) {
  TestEvent event = TestEvent::NOTHING;
  EXPECT_THROW(TestOnSuccess(TestException::ThrowException, &event), std::out_of_range);
  EXPECT_EQ(event, TestEvent::NOTHING);
}


void TestOnFail(TestException testExceptionType, TestEvent * event) {
  auto ScopeGuardOnFail = SG::setScopeGuardOnFail([&event]{
    *event = TestEvent::EVENT;
  });
  if (testExceptionType == TestException::ThrowException) {
    throw std::out_of_range("test_exception");
  }
}

TEST(ScopeGuardOnFailTests, TestOnFailNoexcept) {
  TestEvent event = TestEvent::NOTHING;
  EXPECT_NO_THROW(TestOnFail(TestException::NoThrowException, &event));
  EXPECT_EQ(event, TestEvent::NOTHING);
}

TEST(ScopeGuardOnFailTests, TestOnFailExcept) {
  TestEvent event = TestEvent::NOTHING;
  EXPECT_THROW(TestOnFail(TestException::ThrowException, &event), std::out_of_range);
  EXPECT_EQ(event, TestEvent::EVENT);
}


void TestOnExit(TestException testExceptionType, TestEvent * event) {
  auto ScopeGuardOnExit = SG::setScopeGuardOnExit([&event]{
    *event = TestEvent::EVENT;
  });
  if (testExceptionType == TestException::ThrowException) {
    throw std::out_of_range("test_exception");
  }
}

TEST(ScopeGuardOnExitTests, TestOnExitNoexcept) {
  TestEvent event = TestEvent::NOTHING;
  EXPECT_NO_THROW(TestOnExit(TestException::NoThrowException, &event));
  EXPECT_EQ(event, TestEvent::EVENT);
}

TEST(ScopeGuardOnExitTests, TestOnExitExcept) {
  TestEvent event = TestEvent::NOTHING;
  EXPECT_THROW(TestOnExit(TestException::ThrowException, &event), std::out_of_range);
  EXPECT_EQ(event, TestEvent::EVENT);
}