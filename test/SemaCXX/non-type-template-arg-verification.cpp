// RUN: %clang_cc1 -std=c++11 -fsyntax-only -verify %s

template <__declname a>
class dn {};
template <__tstring a>
class ts {};
template <int a>
class i {};
template <typename a>
class ty {};

template <__declname a>
void dn_dn(dn<a>) {}
template <__tstring a>
void dn_ts(dn<a>) {} // expected-error {{only declname literals}}
template <int a>
void dn_i(dn<a>) {} // expected-error {{only declname literals}}

template <__declname a>
void ts_dn(ts<a>) {} // expected-error {{only string literals}}
template <__tstring a>
void ts_ts(ts<a>) {}
template <int a>
void ts_i(ts<a>) {} // expected-error {{only string literals}}

template <__declname a>
void i_dn(i<a>) {} // expected-note {{only declname literals}}
template <__tstring a>
void i_ts(i<a>) {} // expected-note {{only string literals}}
template <int a>
void i_i(i<a>) {}

void f() {
  dn_dn(dn<`foo`>());
  dn_ts(dn<`foo`>()); // expected-error {{no matching function}}
  dn_i(dn<`foo`>()); // expected-error {{no matching function}}
  ts_dn(ts<"foo">()); // expected-error {{no matching function}}
  ts_ts(ts<"foo">());
  ts_i(ts<"foo">()); // expected-error {{no matching function}}
  i_dn(i<1>()); // expected-error {{no matching function}}
  i_ts(i<1>()); // expected-error {{no matching function}}
  i_i(i<1>());
}
