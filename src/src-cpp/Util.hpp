#pragma once

#include <memory>   // unique_ptr
#include <optional> // optional

namespace combview {

// default renaming of std::unique_ptr (too long!!)
template<class T>
using uptr = std::unique_ptr<T>;

// default renaming of std::observer_ptr (too long!!)
//template<class T>
//using optr = std::observer_ptr<T>;

// default renaming of std::optional (too long!!)
template<class T>
using op = std::optional<T>;

// id type for move id, neighborhood id, etc.
using id_type = std::size_t;

} // namespace combview
