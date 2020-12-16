#pragma once

template<typename Head, typename Tail> 
struct TypeList;

struct NullType {};

template<>
struct TypeList<NullType, NullType> {
	using Head = NullType;
	using Tail = NullType;
};

template<typename A>
struct TypeList<A, NullType> {
	using Head = A;
	using Tail = NullType;
};
