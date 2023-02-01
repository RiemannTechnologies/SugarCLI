#pragma once
#include <type_traits>
#include <SugarInput/lib/Datatypes/Container.h>
namespace Sugar::CLI {

template<typename T>
constexpr bool is_containter(T)
{
	return;
}

}