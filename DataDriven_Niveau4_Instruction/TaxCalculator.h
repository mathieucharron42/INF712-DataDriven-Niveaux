#pragma once

#include "DataManager.h"
#include "VM.h"

#include "Common/Ensure.h"

class TaxCalculator
{
public:
	TaxCalculator(const DataManager& dataManager)
		: _globalTaxData(dataManager.GetGlobalTaxData())
	{ }

	float ComputeFinalPrice(float price)
	{
		float finalPrice = 0;

		std::optional<float> executionResult = VM().Execute(_globalTaxData.ComputationFunction, price);
		if (ensure(executionResult.has_value()))
		{
			finalPrice = executionResult.value();
		}
		
		return finalPrice;
	}

private:
	const GlobalTaxData& _globalTaxData;
	
};