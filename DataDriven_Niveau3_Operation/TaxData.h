#pragma once

#include <string>

enum class TaxApplicationMode
{
	Multiplicative,
	FixedAdditive
};

struct TaxData
{
	std::string Id;
	float Value;
	int ApplicationOrder;
	TaxApplicationMode ApplicationMode;
};