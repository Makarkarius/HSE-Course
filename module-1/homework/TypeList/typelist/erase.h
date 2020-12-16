#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

template<typename TargetType>
struct Erase<NullType, TargetType> {
	using NewTypeList = NullType;
};

template<typename A, typename B>
struct Erase<TypeList<A, B>, A> {
	using NewTypeList = B;
};

template<typename A, typename B, typename TargetType>
struct Erase<TypeList<A, B>, TargetType> {
	using NewTypeList = TypeList<A, typename Erase<B, TargetType>::NewTypeList>;
};
