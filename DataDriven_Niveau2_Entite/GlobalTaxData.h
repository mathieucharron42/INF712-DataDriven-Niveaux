#pragma once

#include "TaxData.h"

#include <vector>

struct GlobalTaxData
{
	std::vector<TaxData> MultiplicativeTaxes;
	std::vector<TaxData> FixedAdditivesTaxes;
};
