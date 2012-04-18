// RUN: %clang_cc1 -std=c++11 -emit-llvm -o - %s | FileCheck %s

template <__tstring s>
void f()
{
  int i = 1;
}

// CHECK: define void @_Z1fIS3fooEvv
template <>
void f<"foo">()
{
  int i = 2;
}

template <__tstring s>
void g()
{
  f<s>();
}

void h()
{
  // CHECK: call void @_Z1fIS3fooEvv
  f<"foo">();
  // CHECK: call void @_Z1fIS3barEvv
  f<"bar">();

  g<"foo">();
  g<"bar">();
}

// CHECK: define linkonce_odr void @_Z1fIS3barEvv

// CHECK: define linkonce_odr void @_Z1gIS3fooEvv
// CHECK: call void @_Z1fIS3fooEvv

// CHECK: define linkonce_odr void @_Z1gIS3barEvv
// CHECK: call void @_Z1fIS3barEvv
