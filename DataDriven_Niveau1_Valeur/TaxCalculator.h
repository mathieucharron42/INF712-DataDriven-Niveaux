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
		finalPrice += (finalPrice * _taxData.TPS);
		finalPrice += (finalPrice * _taxData.TVQ);
		return finalPrice;
	}

private:
	const GlobalTaxData& _taxData;
};