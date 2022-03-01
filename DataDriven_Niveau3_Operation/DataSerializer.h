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
			.Add<GlobalTaxData>("GlobalTaxData")
			.Add<TaxData>("TaxData")
			.Add<std::vector<TaxData>>("vector<TaxData>")
			.Add<std::string>("string")
			.Add<int>("int")
			.Add<TaxApplicationMode>("TaxApplicationMode")
		.Build();

		TypeDescriptor globalTaxDataDescriptor = TypeDescriptorFactory<GlobalTaxData>(typeLibrary)
			.RegisterMember(&GlobalTaxData::Taxes, "Taxes")
		.Build();

		TypeDescriptor taxDataDescriptor = TypeDescriptorFactory<TaxData>(typeLibrary)
			.RegisterMember(&TaxData::Id, "Id")
			.RegisterMember(&TaxData::Value, "Value")
			.RegisterMember(&TaxData::ApplicationOrder, "ApplicationOrder")
			.RegisterMember(&TaxData::ApplicationMode, "ApplicationMode")
		.Build();

		TypeDescriptor taxApplicationModeDescriptor = TypeDescriptorFactory<TaxApplicationMode>(typeLibrary)
			.RegisterValue(TaxApplicationMode::FixedAdditive, "FixedAdditive")
			.RegisterValue(TaxApplicationMode::Multiplicative, "Multiplicative")
		.Build();

		Serializer serializer = SerializerFactory(typeLibrary)
			.LearnType<TaxData, ObjectSerializationStrategy<TaxData>>(taxDataDescriptor)
			.LearnType<GlobalTaxData, ObjectSerializationStrategy<GlobalTaxData>>(globalTaxDataDescriptor)
			.LearnType<std::vector<TaxData>, VectorSerializationStrategy<std::vector<TaxData>>>()
			.LearnType<float, FloatSerializationStrategy>()
			.LearnType<std::string, StringSerializationStrategy>()
			.LearnType<int, Int32SerializationStrategy>()
			.LearnType<TaxApplicationMode, EnumSerializationStrategy<TaxApplicationMode>>(taxApplicationModeDescriptor)
			.SetFormat(SerializationFormat::Short)
		.Build();

		return serializer;
	}
}