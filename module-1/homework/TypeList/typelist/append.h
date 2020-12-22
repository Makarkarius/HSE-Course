#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<>
struct Append<NullType, NullType> {
	using NewTypeList = NullType;
};

template<typename A, typename B, typename NewType>
struct Append<TypeList<A, B>, NewType> {
	using NewTypeList = TypeList<A, typename Append<B, NewType>::NewTypeList>;
};

template<typename T>
struct Append<NullType, T> {
	using NewTypeList = TypeList<T, NullType>;
};

template<typename A, typename B>
struct Append<TypeList<A, B>, NullType> {
	using NewTypeList = TypeList<A, B>;
};

