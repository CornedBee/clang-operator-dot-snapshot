// RUN: %clang_cc1 -std=c++11 -fsyntax-only -verify %s

int main() {
  (void)`foo`; // expected-error {{declname literals are not yet supported}}
}
