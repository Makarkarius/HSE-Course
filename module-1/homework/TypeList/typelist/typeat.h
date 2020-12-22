#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

template<typename A, typename B, unsigned int index>
struct TypeAt<TypeList<A, B>, index> {
	typedef typename TypeAt<B, index - 1>::TargetType TargetType;
};

template<typename A, typename B>
struct TypeAt<TypeList<A, B>, 0> {
	typedef A TargetType;
};