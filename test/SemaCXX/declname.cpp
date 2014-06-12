// RUN: %clang_cc1 -std=c++11 -fsyntax-only -verify %s

int main() {
  (void)``; // expected-error {{expected unqualified-id}}
  (void)`foo bar`; // expected-error {{expected '`'}}
  (void)`+`; // expected-error {{expected unqualified-id}}
  (void)`foo`; // expected-error {{declname literals are not yet supported}}
  (void)` foo`; // expected-error {{declname literals are not yet supported}}
  (void)`foo `; // expected-error {{declname literals are not yet supported}}
  (void)`operator+`; // expected-error {{declname literals are not yet supported}}
  (void)`template foo<int>`; // expected-error {{declname literals are not yet supported}}
}
