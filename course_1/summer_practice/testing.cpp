#include <gtest/gtest.h>
#include <string>
#include "scope_guard.h"

// Todo как сделать без копипаста, но с другой стороны это ведь unit-testы там не нужная сложная логика
enum TestEvent {
  NOTHING,
  EVENT
};

void TestOnSuccess(TestEvent * event, const bool &doExcept) {
  auto ScopeGuardOnSuccess = SG::setScopeGuardOnSuccess([&event]{
    *event = EVENT;
  });
  if (doExcept) {
    throw std::out_of_range("test_exception");
  }
}

TEST(ScopeGuardOnSuccessTests, TestOnSuccessNoexcept) {
  TestEvent event = NOTHING;
  const bool doExcept = false;
  EXPECT_NO_THROW(TestOnSuccess(&event, doExcept));
  EXPECT_EQ(event, EVENT);
}

TEST(ScopeGuardOnSuccessTests, TestOnSuccessExcept) {
  TestEvent event = NOTHING;
  const bool doExcept = true;
  EXPECT_THROW(TestOnSuccess(&event, doExcept), std::out_of_range);
  EXPECT_EQ(event, NOTHING);
}


void TestOnFail(TestEvent * event, const bool &doExcept) {
  auto ScopeGuardOnFail = SG::setScopeGuardOnFail([&event]{
    *event = EVENT;
  });
  if (doExcept) {
    throw std::out_of_range("test_exception");
  }
}

TEST(ScopeGuardOnFailTests, TestOnFailNoexcept) {
  TestEvent event = NOTHING;
  const bool doExcept = false;
  EXPECT_NO_THROW(TestOnFail(&event, doExcept));
  EXPECT_EQ(event, NOTHING);
}

TEST(ScopeGuardOnFailTests, TestOnFailExcept) {
  TestEvent event = NOTHING;
  const bool doExcept = true;
  EXPECT_THROW(TestOnFail(&event, doExcept), std::out_of_range);
  EXPECT_EQ(event, EVENT);
}


void TestOnExit(TestEvent * event, const bool &doExcept) {
  auto ScopeGuardOnExit = SG::setScopeGuardOnExit([&event]{
    *event = EVENT;
  });
  if (doExcept) {
    throw std::out_of_range("test_exception");
  }
}

TEST(ScopeGuardOnExitTests, TestOnExitNoexcept) {
  TestEvent event = NOTHING;
  const bool doExcept = false;
  EXPECT_NO_THROW(TestOnExit(&event, doExcept));
  EXPECT_EQ(event, EVENT);
}

TEST(ScopeGuardOnExitTests, TestOnExitExcept) {
  TestEvent event = NOTHING;
  const bool doExcept = true;
  EXPECT_THROW(TestOnExit(&event, doExcept), std::out_of_range);
  EXPECT_EQ(event, EVENT);
}