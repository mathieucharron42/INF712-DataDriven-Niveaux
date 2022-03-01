#pragma once

#include <string>
#include <vector>

struct TaxData
{
	std::string Id;
	float Value;

	float Compute(float amount) const
	{
		return amount * Value;
	}
};

struct GlobalTaxData
{
	TaxData TPS;
	TaxData TVQ;
};
