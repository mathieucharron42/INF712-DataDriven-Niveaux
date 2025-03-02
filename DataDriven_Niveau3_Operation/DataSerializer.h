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
			.Add<int>("int")
			.BeginType<TaxApplicationMode>("TaxApplicationMode")
				.RegisterValue(TaxApplicationMode::Additive, "Additive")
				.RegisterValue(TaxApplicationMode::Multiplicative, "Multiplicative")
			.EndType<TaxApplicationMode>()
			.BeginType<TaxData>("TaxData")
				.RegisterMember(&TaxData::Id, "Id")
				.RegisterMember(&TaxData::Value, "Value")
				.RegisterMember(&TaxData::ApplicationOrder, "ApplicationOrder")
				.RegisterMember(&TaxData::ApplicationMode, "ApplicationMode")
			.EndType<TaxData>()
			.Add<std::vector<TaxData>>("std::vector<TaxData>")
			.BeginType<GlobalTaxData>("GlobalTaxData")
				.RegisterMember(&GlobalTaxData::Taxes, "Taxes")
			.EndType<GlobalTaxData>()
		.Build();

		Serialization::Serializer serializer = Serialization::SerializerFactory(typeLibrary)
			.LearnType<float, Serialization::FloatSerializationStrategy>()
			.LearnType<std::string, Serialization::StringSerializationStrategy>()
			.LearnType<int, Serialization::Int32SerializationStrategy>()
			.LearnType<TaxApplicationMode, Serialization::EnumSerializationStrategy<TaxApplicationMode>>()
			.LearnType<TaxData, Serialization::ObjectSerializationStrategy<TaxData>>()
			.LearnType<std::vector<TaxData>, Serialization::VectorSerializationStrategy<std::vector<TaxData>>>()
			.LearnType<GlobalTaxData, Serialization::ObjectSerializationStrategy<GlobalTaxData>>()
			.SetFormat(Serialization::SerializationFormat::Short)
		.Build();

		return serializer;
	}
}