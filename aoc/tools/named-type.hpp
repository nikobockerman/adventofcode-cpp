
#include <type_traits>

template <typename T, typename Parameter>
class NamedType {
 public:
  explicit constexpr NamedType(T value) : value{value} {}

  [[nodiscard]] constexpr auto get() noexcept -> T& { return value; }
  [[nodiscard]] constexpr auto get() const noexcept
      -> std::remove_reference_t<T> const& {
    return value;
  }

 private:
  T value;
};
