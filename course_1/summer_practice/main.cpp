#include <iostream>
#include <exception>


namespace SG {
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

  template <typename Ftype, bool executeOnException>
  class ScopeGuard {
   private:
    UncaughtExceptionCounter exceptionCounter_;
    Ftype function_;

   public:
    ScopeGuard(Ftype&& fn)
        : function_(std::forward<Ftype>(fn))
    {}

    ~ScopeGuard() noexcept (executeOnException) {
      if (executeOnException == exceptionCounter_.isNewUncaughtException()) {
        function_();
      }
    }
  };

  template <typename Ftype>
  auto ScopeGuardByFail(Ftype&& fn) {
    return ScopeGuard<Ftype, true>(std::forward<Ftype>(fn));
  }

  template <typename Ftype>
  auto ScopeGuardByExit(Ftype&& fn) {
    return ScopeGuard<Ftype, true>(std::forward<Ftype>(fn));
  };

  template <typename Ftype>
  auto ScopeGuardBySuccess(Ftype&& fn) {
    return ScopeGuard<Ftype, false>(std::forward<Ftype>(fn));
  };
}

void kek() noexcept {
  auto memes = SG::ScopeGuardByFail([]{ std::cout << "FAIL" << '\n'; });
//  ScopeGuard::ScopeGuardByFail<std::function<typeid(lambda_kek).name()>> sh(lambda_kek);
  int mems = 228;
  throw 1;
}

int main() {
  kek();
  return 0;
}