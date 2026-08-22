#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <memory>
#include <functional>

template <class Derived, class Base>
concept DerivedFrom = std::is_base_of_v<Base, Derived>;

template <class Base, class... Args>
using Factory = std::function<std::unique_ptr<Base>(Args&&...)>;

template <class Base, class Derived, class... Args>
requires DerivedFrom<Derived, Base>
std::unique_ptr<Base> create(Args... args) {
  return std::make_unique<Derived>(std::forward<Args>(args)...);
};

#endif