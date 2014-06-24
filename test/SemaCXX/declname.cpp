// RUN: %clang_cc1 -std=c++11 -fsyntax-only -verify %s

void test() {
  (void)``; // expected-error {{expected unqualified-id}}
  (void)`foo bar`; // expected-error {{expected '`'}}
  (void)`+`; // expected-error {{expected unqualified-id}}
  (void)`foo`;
  (void)` foo`;
  (void)`foo `;
  (void)`operator+`;
  (void)`template foo<int>`;
}
