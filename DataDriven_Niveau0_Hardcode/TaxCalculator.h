#pragma once

class TaxCalculator
{
public:
	float ComputeFinalPrice(float price)
	{
		float finalPrice = price;
		finalPrice *= (1 + TPS);
		finalPrice *= (1 + TVQ);
		finalPrice += EHF;
		return finalPrice;
	}

private:
	static constexpr float TPS = 0.05f;
	static constexpr float TVQ = 0.0975f;
	static constexpr float EHF = 1.1f;
};