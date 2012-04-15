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

void g()
{
  // CHECK: call void @_Z1fIS3fooEvv
  f<"foo">();
  // CHECK: call void @_Z1fIS3barEvv
  f<"bar">();
}

// CHECK: define linkonce_odr void @_Z1fIS3barEvv
