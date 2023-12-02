#pragma once

namespace Ty {

using c_string = char const*;

using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;

using i8  = char;
using i16 = short;
using i32 = int;
using i64 = long;

static_assert(sizeof(u8)  == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(u64) == 8);

static_assert(sizeof(i8)  == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

using usize = __SIZE_TYPE__; 
#define unsigned signed // NOLINT
using isize = __SIZE_TYPE__;
#undef unsigned

}

using Ty::c_string;

using Ty::u8;
using Ty::u16;
using Ty::u32;
using Ty::u64;

using Ty::i8;
using Ty::i16;
using Ty::i32;
using Ty::i64;

using Ty::usize;
using Ty::isize;
