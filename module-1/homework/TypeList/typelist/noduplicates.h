#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<>
struct NoDuplicates<NullType> {
	using NewTypeList = NullType;
};

template<typename A, typename TList>
struct NoDuplicates<TypeList<A, TypeList<A, TList>>> {
	using NewTypeList = TypeList<A, typename NoDuplicates<TList>::NewTypeList>;
};
