#include <string>
#include <cmath>
#include <iostream>
#include "logger.h"

/**
 * Inheritance: methods hiding
 */
class Base {
public:
  Base(int key);

  inline int getKey() const {
    return m_key;
  }
  
  size_t hashCode() const;

private:
  int m_key;
};

Base::Base(int key)
  : m_key(key) {
  DBG("Base ctor: %i", key);
}

size_t Base::hashCode() const {
  return static_cast<size_t>(m_key);
}

// ----------------------------------------------
class Derived : public Base {
public:
  Derived(int key, const std::string& value);

  inline const std::string& getValue() const {
    return m_value;
  }
  
  size_t hashCode() const;  // hiding

private:
  std::string m_value;
};

Derived::Derived(int key, const std::string& value)
  : Base(key), m_value(value) {
  INF("Derived ctor: %i %s", key, value.c_str());
}

size_t Derived::hashCode() const {
  size_t base_code = Base::hashCode();
  
  // Java String hash code: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
  int prime = 31;
  size_t hash = 0;
  int power = m_value.length() - 1;

  for (auto it = m_value.begin(); it != m_value.end(); ++it, --power) {
    hash += static_cast<size_t>(*it) * std::pow(prime, power);
  }
  
  return base_code + hash;
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Inheritance 5");

  Derived derived(5, "Lorem");
  std::cout << "Key: " << derived.getKey() << ", Value: " << derived.getValue() << ", Hash: " << derived.hashCode() << std::endl;

  DBG("[Lesson 5]: Inheritance 5 [END]");
  return 0;
}
