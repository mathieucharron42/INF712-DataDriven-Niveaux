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
		finalPrice += ComputeMultiplicative(_taxData.TPS, finalPrice);
		finalPrice += ComputeMultiplicative(_taxData.TVQ, finalPrice);
		finalPrice += ComputeAdditive(_taxData.EHF, finalPrice);
		return finalPrice;
	}

private:
	static float ComputeMultiplicative(float value, float price)
	{
		return price * value;
	}

	static float ComputeAdditive(float value, float price)
	{
		return value;
	}

	const GlobalTaxData& _taxData;
};