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
			{ TaxApplicationMode::Multiplicative, &ApplyMultiplicative },
			{ TaxApplicationMode::FixedAdditive, &ApplyFixedAdditive }
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
				finalPrice = (*applicationModeFunc)(taxData, finalPrice);
			}
			
		}
		return finalPrice;
	}

private:
	static float ApplyMultiplicative(TaxData taxData, float price)
	{
		return price * (1 + taxData.Value);
	}

	static float ApplyFixedAdditive(TaxData taxData, float price)
	{
		return price + taxData.Value;
	}

	const GlobalTaxData& _taxData;
	const TaxApplicationMapping _taxApplicationMapping;
};