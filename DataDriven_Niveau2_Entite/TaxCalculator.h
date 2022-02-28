#pragma once

#include "DataManager.h"
#include "TaxData.h"

class TaxCalculator
{
public:
	TaxCalculator(const DataManager& dataManager)
		: _globalTaxData(dataManager.GetGlobalTaxData())
	{ }

	float ComputeFinalPrice(float price)
	{
		float finalPrice = price;
		for(TaxData multiplicativeTaxData : _globalTaxData.MultiplicativeTaxes)
		{
			finalPrice *= (1 + multiplicativeTaxData.Value);
		}
		for (TaxData fixedAdditiveTaxData : _globalTaxData.FixedAdditivesTaxes)
		{
			finalPrice += fixedAdditiveTaxData.Value;
		}
		return finalPrice;
	}

private:
	const GlobalTaxData& _globalTaxData;
};