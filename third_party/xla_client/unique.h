#ifndef TENSORFLOW_COMPILER_XLA_XLA_CLIENT_UNIQUE_H_
#define TENSORFLOW_COMPILER_XLA_XLA_CLIENT_UNIQUE_H_

#include <functional>

#include "absl/types/optional.h"
#include "tensorflow/compiler/xla/xla_client/debug_macros.h"

namespace xla {
namespace util {

// Helper class to allow tracking zero or more things, which should be forcibly
// be one only thing.
template <typename T, typename C = std::equal_to<T>>
class Unique {
 public:
  std::pair<bool, const T&> set(const T& value) {
    if (value_) {
      XLA_CHECK(C()(*value_, value))
          << "'" << *value_ << "' vs '" << value << "'";
      return std::pair<bool, const T&>(false, *value_);
    }
    value_ = value;
    return std::pair<bool, const T&>(true, *value_);
  }

  operator bool() const { return value_.has_value(); }
  operator const T&() const { return *value_; }
  const T& operator*() const { return *value_; }
  const T* operator->() const { return value_.operator->(); }

 private:
  absl::optional<T> value_;
};

}  // namespace util
}  // namespace xla

#endif  // TENSORFLOW_COMPILER_XLA_XLA_CLIENT_UNIQUE_H_
