#include <iostream>
#include <exception>


namespace ScopeGuard {
  class UncaughtExceptionCounter {
   private:
    int exceptionCount_;
   public:
    UncaughtExceptionCounter()
        : exceptionCount_(std::uncaught_exceptions())
    {}

    bool isNewUncaughtException() noexcept {
      return std::uncaught_exceptions() > exceptionCount_;
    }
  };

  class ScopeGuardByFail {
   private:
    UncaughtExceptionCounter exceptionCounter_;

   public:
    ~ScopeGuardByFail() {
      if (!exceptionCounter_.isNewUncaughtException()) {
        std::cout << "EXCEPTION BLYA" << '\n';
      } else {
        std::cout << "NUHIYA" << '\n';
      }
    }
  };
}

void kek() {
  ScopeGuard::ScopeGuardByFail sh;
  int mems = 228;
}

int main() {
  kek();
  return 0;
}