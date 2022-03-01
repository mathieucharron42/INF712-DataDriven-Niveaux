#pragma once

#include "DataManager.h"
#include "TaxData.h"

class TaxCalculator
{
public:
	using TaxApplicationFunc = std::function<float(const TaxData&, float)>;
	using TaxApplicationMapping = std::map<TaxApplicationMode, TaxApplicationFunc>;

	TaxCalculator(const DataManager& dataManager)
		: _taxData(dataManager.GetTaxData())
		, _taxApplicationMapping({
			{ TaxApplicationMode::Multiplicative, &ComputeMultiplicative },
			{ TaxApplicationMode::Additive, &ComputeAdditive }
		})
	{ }

	float ComputeFinalPrice(float price)
	{
		float finalPrice = price;

		std::vector<TaxData> sortedTaxes = _taxData.Taxes;
		std::sort(sortedTaxes.begin(), sortedTaxes.end(), [](const TaxData& t1, const TaxData& t2)
		{
			return t1.ApplicationOrder < t2.ApplicationOrder;
		});

		for (const TaxData& taxData : sortedTaxes)
		{
			const auto found = _taxApplicationMapping.find(taxData.ApplicationMode);
			const TaxApplicationFunc* applicationModeFunc = found != _taxApplicationMapping.end() ? &found->second : nullptr;
			if (ensure(applicationModeFunc))
			{
				finalPrice += (*applicationModeFunc)(taxData, finalPrice);
			}
			
		}
		return finalPrice;
	}

private:
	static float ComputeMultiplicative(TaxData taxData, float price)
	{
		return price * taxData.Value;
	}

	static float ComputeAdditive(TaxData taxData, float price)
	{
		return taxData.Value;
	}

	const GlobalTaxData& _taxData;
	const TaxApplicationMapping _taxApplicationMapping;
};