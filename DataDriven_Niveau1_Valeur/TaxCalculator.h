#pragma once

#include "DataManager.h"
#include "TaxData.h"

class TaxCalculator
{
public:
	TaxCalculator(const DataManager& dataManager)
		: _taxData(dataManager.GetTaxData())
	{ }

	float ComputeFinalPrice(float price)
	{
		float finalPrice = price;
		finalPrice *= (1 + _taxData.TPS);
		finalPrice *= (1 + _taxData.TVQ);
		return finalPrice;
	}

private:
	const TaxData& _taxData;
};