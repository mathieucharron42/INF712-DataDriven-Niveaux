#pragma once

#include <string>
#include <vector>

struct TaxData
{
	std::string Id;
	float Value;
};

struct MultiplicativeTaxData : public TaxData
{

};

struct AdditiveTaxData : public TaxData
{

};

struct GlobalTaxData
{
	MultiplicativeTaxData TPS;
	MultiplicativeTaxData TVQ;
	AdditiveTaxData EHF;
};
