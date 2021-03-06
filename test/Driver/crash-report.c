// RUN: rm -rf %t
// RUN: mkdir %t
// RUN: not env TMPDIR=%t TEMP=%t TMP=%t RC_DEBUG_OPTIONS=1 %clang -fsyntax-only %s \
// RUN:  -F/tmp/ -I /tmp/ -idirafter /tmp/ -iquote /tmp/ -isystem /tmp/ \
// RUN:  -iprefix /the/prefix -iwithprefix /tmp -iwithprefixbefore /tmp/ \
// RUN:  -fmodules -fcxx-modules -fmodules-cache-path=/tmp/              \
// RUN:  -Xclang -internal-isystem -Xclang /tmp/                         \
// RUN:  -Xclang -internal-externc-isystem -Xclang /tmp/                 \
// RUN:  -DFOO=BAR 2>&1 | FileCheck %s
// RUN: cat %t/crash-report-*.c | FileCheck --check-prefix=CHECKSRC %s
// RUN: cat %t/crash-report-*.sh | FileCheck --check-prefix=CHECKSH %s
// REQUIRES: crash-recovery

// because of the glob (*.c, *.sh)
// REQUIRES: shell

// RUN: not env FORCE_CLANG_DIAGNOSTICS_CRASH=1 %clang -fsyntax-only -x c /dev/null -lstdc++ 2>&1 | FileCheck %s

// FIXME: Investigating. "fatal error: file 'nul' modified since it was first processed"
// XFAIL: mingw32

#pragma clang __debug parser_crash
// CHECK: Preprocessed source(s) and associated run script(s) are located at:
// CHECK-NEXT: note: diagnostic msg: {{.*}}.c
FOO
// CHECKSRC: FOO
// CHECKSH: -cc1
// CHECKSH: -D "FOO=BAR"
// CHECKSH-NOT: -F/tmp/
// CHECKSH-NOT: -I /tmp/
// CHECKSH-NOT: -idirafter /tmp/
// CHECKSH-NOT: -iquote /tmp/
// CHECKSH-NOT: -isystem /tmp/
// CHECKSH-NOT: -iprefix /the/prefix
// CHECKSH-NOT: -iwithprefix /tmp/
// CHECKSH-NOT: -iwithprefixbefore /tmp/
// CHECKSH-NOT: -fmodules-cache-path=/tmp/
// CHECKSH-NOT: -internal-isystem /tmp/
// CHECKSH-NOT: -internal-externc-isystem /tmp/
// CHECKSH-NOT: -dwarf-debug-flags
