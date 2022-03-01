#pragma once

#include "DataSerializer.h"
#include "TaxData.h"

#include "Serialization/Reader/JsonSerializationReader.h"
#include "Serialization/Serializer.h"
#include "Serialization/Writer/JsonSerializationWriter.h"

#include <fstream>

using namespace Reflecto;
using namespace Reflecto::Reflection;
using namespace Reflecto::Serialization;

class DataManager
{
public:
	bool Initialize()
	{
		bool success = false;

		Serializer serializer = BuildSerializer();

		std::ifstream ifs("tax_data.json");
		if (ifs.is_open())
		{
			JsonSerializationReader reader;
			if (reader.Import(ifs))
			{
				success = ensure(serializer.Deserialize(_tax, reader));
			}
		}

		return success;
	}

	const GlobalTaxData& GetTaxData() const
	{
		return _tax;
	}

private:
	GlobalTaxData _tax;
};