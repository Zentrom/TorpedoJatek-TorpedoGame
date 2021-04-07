#pragma once

#include <array>

//Kliens �s szervern�l is sz�ks�ges glob�lis v�ltoz�k

//Hajoszam a palyanagysag fuggvenyeben(1x1,2x2,stb.)
namespace ShipCount {
	const std::array<int, 4> Five = { 3,1,1,0 };
	const std::array<int, 4> Seven = { 4,3,2,0 };
	const std::array<int, 4> Nine = { 6,4,3,1 };
}