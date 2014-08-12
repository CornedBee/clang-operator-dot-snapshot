// RUN: %clang_cc1 -std=c++1y -fsyntax-only %s
// expected-no-diagnostics

struct ref {
  int i;
  void* p;
};

struct sdot1 {
  template <__tstring n>
  decltype(auto) operator .() {
    return (r.*n);
  }
  template <__tstring n>
  decltype(auto) operator .() const {
    return (r.*n);
  }

  ref r;
};

struct ndot1 {
  template <__declname n>
  decltype(auto) operator .() {
    return (r.*n);
  }
  template <__declname n>
  decltype(auto) operator .() const {
    return (r.*n);
  }

  ref r;
};

template <typename S>
struct ndot2 {
  template <__declname n>
  decltype(auto) operator .() {
    return (r.*n);
  }
  template <__declname n>
  decltype(auto) operator .() const {
    return (r.*n);
  }

  S r;
};

template <typename S>
void tfn() {
  ndot2<S> n;
  n.i = 0;
  n.p = &n;
}

void test() {
  sdot1 s;
  s.i = 1;
  s.p = &s;

  ndot1 n;
  n.i = 1;
  n.p = &n;

  tfn<ref>();
}
