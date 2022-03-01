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
		finalPrice += _taxData.TPS.Compute(finalPrice);
		finalPrice += _taxData.TVQ.Compute(finalPrice);
		return finalPrice;
	}

private:
	const GlobalTaxData& _taxData;
};