// RUN: %clang_cc1 -std=c++11 -emit-llvm -o - %s | FileCheck %s

template <__declname n>
void f()
{
  int i = 1;
}

// CHECK: define void @_Z1fIN3fooEEvv
template <>
void f<`foo`>()
{
  // CHECK: store i32 2
  int i = 2;
}

template <__declname n>
void g()
{
  f<n>();
}

void h()
{
  // CHECK: call void @_Z1fIN3fooEEvv
  f<`foo`>();
  // CHECK: call void @_Z1fIN3barEEvv
  f<`bar`>();

  g<`foo`>();
  g<`bar`>();
}

template <__declname n>
class fooc {};

template <__declname n>
void foocf(fooc<n>) {}

void i() {
  fooc<`foo`> fc;
  foocf(fc);
}

struct x { int i; };

template <__declname n>
void j() {
  x v;
  v.*n = 1;
}

void k() {
  j<`i`>();
}

// CHECK: define linkonce_odr void @_Z1fIN3barEEvv

// CHECK: define linkonce_odr void @_Z1gIN3fooEEvv
// CHECK: call void @_Z1fIN3fooEEvv

// CHECK: define linkonce_odr void @_Z1gIN3barEEvv
// CHECK: call void @_Z1fIN3barEEvv

// CHECK: define linkonce_odr void @_Z1jIN1iEEvv
// CHECK: getelementptr {{.*}}, i32 0, i32 0
// CHECK: store i32 1
