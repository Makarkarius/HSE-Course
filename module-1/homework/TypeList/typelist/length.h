#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<>
struct Length<NullType> {
	static size_t const length = 0;
};

template<typename A, typename B>
struct Length<TypeList<A, B>> {
	static size_t const length = Length<B>::length + 1;
};