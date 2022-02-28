#pragma once

#include <string>

namespace TaxApplicationMode
{
	inline static const std::string Multiplicative = "Multiplicative";
	inline static const std::string FixedAdditive = "FixedAdditive";
};

struct TaxData
{
	std::string Id;
	float Value;
	int ApplicationOrder;
	std::string ApplicationMode;
};