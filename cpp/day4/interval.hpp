#include <iostream>

template <typename TypeT> class Interval {
public:
  Interval(TypeT lower, TypeT upper) { setBounds(lower, upper); }
  void setBounds(TypeT lower, TypeT upper) {
    if (upper < lower) {
      throw std::runtime_error("Upper bound is smaller than lower bound!");
    }
    m_upper_bound = upper;
    m_lower_bound = lower;
  }

  bool includes(Interval &other) {
    return (this->m_upper_bound >= other.m_upper_bound &&
            this->m_lower_bound <= other.m_lower_bound);
  }

  bool intersects(Interval &other) {
    bool other_lower_inside{this->m_lower_bound <= other.m_lower_bound &&
                            this->m_upper_bound >= other.m_lower_bound};
    bool other_upper_inside{this->m_lower_bound <= other.m_upper_bound &&
                            this->m_upper_bound >= other.m_upper_bound};

    bool other_includes_this{other.includes(*this)};

    return other_lower_inside || other_upper_inside || other_includes_this;
  }

private:
  TypeT m_upper_bound;
  TypeT m_lower_bound;
};
