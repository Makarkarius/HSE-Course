#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template<typename TList>
struct EraseAll<TList, NullType> {
	using NewTypeList = TList;
};

template<typename TargetType>
struct EraseAll<NullType, TargetType> {
	using NewTypeList = NullType;
};

template<typename A, typename B>
struct EraseAll<TypeList<A, B>, A> {
	using NewTypeList = typename EraseAll<B, A>::NewTypeList;
};

template<typename A, typename B, typename TargetType>
struct EraseAll<TypeList<A, B>, TargetType> {
	using NewTypeList = TypeList<A, typename EraseAll<B, TargetType>::NewTypeList>;
};
