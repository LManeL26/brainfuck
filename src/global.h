#ifndef GLOBAL_FLAG
#define GLOBAL_FLAG

#define nameof(x) #x

#pragma region Primitives

typedef unsigned long long int u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;


typedef signed long long int i64;
typedef signed int i32;
typedef signed short i16;
typedef signed char i8;

typedef double f64;
typedef float f32;


typedef u8 bool;

#define true (1 == 1)
#define false (1 != 1)


#pragma endregion

#endif