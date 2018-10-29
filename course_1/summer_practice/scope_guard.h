//
// Created by MacBook on 24.10.2018.
//

#ifndef SCOPE_GUARD_SCOPE_GUARD_H
#define SCOPE_GUARD_SCOPE_GUARD_H

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
  bool needToReact() const;
};

template <>
class ConditionDetector<OnFail> : public ConditionDetectorBase {
 public:
  bool needToReact() const;
};

template <>
class ConditionDetector<OnSuccess> : public ConditionDetectorBase {
 public:
  bool needToReact() const;
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

bool ConditionDetector<OnExit>::needToReact() const {
  return true;
}

bool ConditionDetector<OnFail>::needToReact() const {
  return std::uncaught_exceptions() > NumExceptions;
}

bool ConditionDetector<OnSuccess>::needToReact() const {
  return NumExceptions == std::uncaught_exceptions();
}

template <typename TActionType>
inline auto setScopeGuardOnFail(TActionType&& fn) {
  return ScopeGuard<TActionType, OnFail>(std::forward<TActionType>(fn));
}

template <typename TActionType>
inline auto setScopeGuardOnExit(TActionType&& fn) {
  return ScopeGuard<TActionType, OnExit>(std::forward<TActionType>(fn));
}

template <typename TActionType>
inline auto setScopeGuardOnSuccess(TActionType&& fn) {
  return ScopeGuard<TActionType, OnSuccess>(std::forward<TActionType>(fn));
}


}

#endif //SCOPE_GUARD_SCOPE_GUARD_H
