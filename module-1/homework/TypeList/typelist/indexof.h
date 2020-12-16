#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename T>
struct IndexOf<NullType, T> {
	static constexpr int pos = -1;
};

template<typename B, typename TargetType>
struct IndexOf<TypeList<TargetType, B>, TargetType> {
	static constexpr int pos = 0;
};

template<typename A, typename B, typename TargetType>
struct IndexOf<TypeList<A, B>, TargetType> {
private:
	static constexpr int ind = IndexOf<B, TargetType>::pos;
public:
	static constexpr int pos = (ind == -1 ? -1 : ind + 1);
};