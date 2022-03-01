#pragma once

#include <string>

#include <vector>

enum class TaxApplicationMode
{
	Multiplicative,
	Additive
};

struct TaxData
{
	std::string Id;
	float Value;
	int ApplicationOrder;
	TaxApplicationMode ApplicationMode;
};

struct GlobalTaxData
{
	std::vector<TaxData> Taxes;
};
