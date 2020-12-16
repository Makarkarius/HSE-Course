#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace {
	using NewTypeList = NullType;
};

template<typename A, typename B, typename NewType>
struct Replace<TypeList<A, B>, A, NewType> {
	using NewTypeList = TypeList<NewType, B>;
};

template<typename A, typename B, typename OldType, typename NewType>
struct Replace<TypeList<A, B>, OldType, NewType> {
	using NewTypeList = TypeList<A, typename Replace<B, OldType, NewType>::NewTypeList>;
};
