#include <iostream>
#include <exception>


namespace SG {
  class ConditionDetectorBase {
   public:
    ConditionDetectorBase()
        : NumExceptions(std::uncaught_exceptions()) {
    }

   protected:
    int NumExceptions;
  };

  template <class>
  class ConditionDetector;

  class OnExit {};
  class OnFail {};
  class OnSuccess {};

  template <>
  class ConditionDetector<OnExit> {
   public:
    bool needToReact() {
      return true;
    }
  };

  template <>
  class ConditionDetector<OnFail> : public ConditionDetectorBase {
   public:
    bool needToReact() {
      return std::uncaught_exceptions() > NumExceptions;
    }
  };

  template <>
  class ConditionDetector<OnSuccess> : public ConditionDetectorBase {
   public:
    bool needToReact() {
      return NumExceptions == std::uncaught_exceptions();
    }
  };

  template <typename TActionType, typename TPolicy>
  class ScopeGuard {
   public:
    ScopeGuard(TActionType&& fn)
        : ResponseAction_(std::forward<TActionType>(fn)) {
    }

    ~ScopeGuard() noexcept {
      if (Detector_.needToReact()) {
        ResponseAction_();
      }
    }

   private:
    ConditionDetector<TPolicy> Detector_;
    TActionType ResponseAction_;
  };

  template <typename Ftype>
  inline auto ScopeGuardOnFail(Ftype&& fn) {
    return ScopeGuard<Ftype, OnFail>(std::forward<Ftype>(fn));
  }

  template <typename Ftype>
  inline auto ScopeGuardOnExit(Ftype&& fn) {
    return ScopeGuard<Ftype, OnExit>(std::forward<Ftype>(fn));
  };

  template <typename Ftype>
  inline auto ScopeGuardOnSuccess(Ftype&& fn) {
    return ScopeGuard<Ftype, OnSuccess>(std::forward<Ftype>(fn));
  };
}

void kek() {
  auto memes = SG::ScopeGuardOnFail([]{ std::cout << "FAIL" << '\n'; });
  std::cout << "first" << '\n';
  throw 1;
}

int main() {
  try {
    kek();
  } catch(...) {
    std::cout << "THE END" << '\n';
  }
  return 0;
}