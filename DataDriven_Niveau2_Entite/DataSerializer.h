#pragma once

#include "TaxData.h"

#include "Common/Ensure.h"
#include "Type/TypeDescriptor.h"
#include "Type/TypeDescriptorFactory.h"
#include "Type/TypeLibrary.h"
#include "Type/TypeLibraryFactory.h"
#include "Serialization/Reader/JsonSerializationReader.h"
#include "Serialization/Serializer.h"
#include "Serialization/SerializerFactory.h"
#include "Serialization/Strategy/SerializationStrategy.h"
#include "Serialization/Writer/JsonSerializationWriter.h"

using namespace Reflecto;
using namespace Reflecto::Reflection;
using namespace Reflecto::Serialization;

namespace
{
	Reflecto::Serialization::Serializer BuildSerializer()
	{
		TypeLibrary typeLibrary = TypeLibraryFactory()
			.Add<float>("float")
			.Add<std::string>("string")
			.BeginType<TaxData>("TaxData")
				.RegisterMember(&TaxData::Id, "Id")
				.RegisterMember(&TaxData::Value, "Value")
			.EndType<TaxData>()
			.Add<std::vector<TaxData>>("vector<TaxData>")
			.Add<MultiplicativeTaxData, TaxData>("MultiplicativeTaxData")
			.Add<AdditiveTaxData, TaxData>("MultiplicativeTaxData")
			.BeginType<GlobalTaxData>("GlobalTaxData")
				.RegisterMember(&GlobalTaxData::TPS, "TPS")
				.RegisterMember(&GlobalTaxData::TVQ, "TVQ")
				.RegisterMember(&GlobalTaxData::EHF, "EHF")
			.EndType<GlobalTaxData>()
		.Build();

		Serialization::Serializer serializer = Serialization::SerializerFactory(typeLibrary)
			.LearnType<float, Serialization::FloatSerializationStrategy>()
			.LearnType<std::string, Serialization::StringSerializationStrategy>()
			.LearnType<std::vector<TaxData>, Serialization::VectorSerializationStrategy<std::vector<TaxData>>>()
			.LearnType<GlobalTaxData, Serialization::ObjectSerializationStrategy<GlobalTaxData>>()
			.LearnType<MultiplicativeTaxData, Serialization::ObjectSerializationStrategy<MultiplicativeTaxData>>()
			.LearnType<AdditiveTaxData, Serialization::ObjectSerializationStrategy<AdditiveTaxData>>()
			.SetFormat(Serialization::SerializationFormat::Short)
		.Build();

		return serializer;
	}
}