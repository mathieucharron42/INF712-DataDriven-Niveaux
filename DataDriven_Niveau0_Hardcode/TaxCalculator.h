#pragma once

class TaxCalculator
{
public:
	TaxCalculator() = default;

	float ComputeFinalPrice(float price)
	{
		float finalPrice = price;
		finalPrice += ComputeMultiplicative(TPS, finalPrice);
		finalPrice += ComputeMultiplicative(TVQ, finalPrice);
		finalPrice += ComputeAdditive(EHF, finalPrice);
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

	static constexpr float TPS = 0.05f;
	static constexpr float TVQ = 0.09975f;
	static constexpr float EHF = 1.25f;
};