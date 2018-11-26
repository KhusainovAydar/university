#include <gtest/gtest.h>
#include <string>
#include "scope_guard.h"

// Todo как сделать без копипаста, но с другой стороны это ведь unit-testы там не нужная сложная логика

const std::string WA_MESSAGE = "Wrong Answer"; // ToDo нужно придумать сообщения
const std::string TEST_EXCEPTION_MESSAGE = "Test exception"; // Todo нужно придумать как проверять сообщение исключения без написания дополнительного предиката или структуры try/catch


void TestOnSuccess(bool &finish, bool doExcept) { // Todo наверно не стоит делать noexcept(!doExcept) но нужно обсудить
  auto ScopeGuardOnSuccess = SG::setScopeGuardOnSuccess([&finish]{
    finish = true;
  });
  if (doExcept) {
    throw std::out_of_range(TEST_EXCEPTION_MESSAGE);
  }
}

TEST(ScopeGuardOnSuccessTests, TestOnSuccessNoexcept) {
  bool good = false;
  EXPECT_NO_THROW(TestOnSuccess(good, false));
  EXPECT_EQ(good, true) << WA_MESSAGE;
}

TEST(ScopeGuardOnSuccessTests, TestOnSuccessExcept) {
  bool good = false;
  EXPECT_THROW(TestOnSuccess(good, true), std::out_of_range); // todo exception std::out_of_range не самый лучший вариант конечно
  EXPECT_EQ(good, false) << WA_MESSAGE;
}


void TestOnFail(bool &finish, bool doExcept) {
  auto ScopeGuardOnFail = SG::setScopeGuardOnFail([&finish]{
    finish = true;
  });
  if (doExcept) {
    throw std::out_of_range(TEST_EXCEPTION_MESSAGE);
  }
}

TEST(ScopeGuardOnFailTests, TestOnFailNoexcept) {
  bool good = false;
  EXPECT_NO_THROW(TestOnFail(good, false));
  EXPECT_EQ(good, false) << WA_MESSAGE;
}

TEST(ScopeGuardOnFailTests, TestOnFailExcept) {
  bool good = false;
  EXPECT_THROW(TestOnFail(good, true), std::out_of_range);
  EXPECT_EQ(good, true) << WA_MESSAGE;
}


void TestOnExit(bool &finish, bool doExcept) {
  auto ScopeGuardOnExit = SG::setScopeGuardOnExit([&finish]{
    finish = true;
  });
  if (doExcept) {
    throw std::out_of_range(TEST_EXCEPTION_MESSAGE);
  }
}

TEST(ScopeGuardOnExitTests, TestOnExitNoexcept) {
  bool good = false;
  EXPECT_NO_THROW(TestOnExit(good, false));
  EXPECT_EQ(good, true) << WA_MESSAGE;
}

TEST(ScopeGuardOnExitTests, TestOnExitExcept) {
  bool good = false;
  EXPECT_THROW(TestOnExit(good, true), std::out_of_range);
  EXPECT_EQ(good, true) << WA_MESSAGE;
}