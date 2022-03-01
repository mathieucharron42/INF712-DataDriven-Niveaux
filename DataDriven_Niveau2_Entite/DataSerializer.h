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
			.Add<AdditiveTaxData>("AdditiveTaxData")
			.Add<MultiplicativeTaxData>("MultiplicativeTaxData")
			.Add<std::vector<TaxData>>("vector<TaxData>")
			.Add<std::string>("string")
		.Build();

		TypeDescriptor globalTaxDataDescriptor = TypeDescriptorFactory<GlobalTaxData>(typeLibrary)
			.RegisterMember(&GlobalTaxData::TPS, "TPS")
			.RegisterMember(&GlobalTaxData::TVQ, "TVQ")
			.RegisterMember(&GlobalTaxData::EHF, "EHF")
		.Build();

		TypeDescriptor taxDataDescriptor = TypeDescriptorFactory<TaxData>(typeLibrary)
			.RegisterMember(&TaxData::Id, "Id")
			.RegisterMember(&TaxData::Value, "Value")
		.Build();

		TypeDescriptor additiveTaxDataDescriptor = TypeDescriptorFactory<AdditiveTaxData>(typeLibrary)
			.RegisterMember(&AdditiveTaxData::Id, "Id")
			.RegisterMember(&AdditiveTaxData::Value, "Value")
		.Build();

		TypeDescriptor multiplicativeTaxDataDescriptor = TypeDescriptorFactory<MultiplicativeTaxData>(typeLibrary)
			.RegisterMember(&MultiplicativeTaxData::Id, "Id")
			.RegisterMember(&MultiplicativeTaxData::Value, "Value")
		.Build();

		Serializer serializer = SerializerFactory(typeLibrary)
			.LearnType<TaxData, ObjectSerializationStrategy<TaxData>>(taxDataDescriptor)
			.LearnType<AdditiveTaxData, ObjectSerializationStrategy<AdditiveTaxData>>(additiveTaxDataDescriptor)
			.LearnType<MultiplicativeTaxData, ObjectSerializationStrategy<MultiplicativeTaxData>>(multiplicativeTaxDataDescriptor)
			.LearnType<GlobalTaxData, ObjectSerializationStrategy<GlobalTaxData>>(globalTaxDataDescriptor)
			.LearnType<std::vector<TaxData>, VectorSerializationStrategy<std::vector<TaxData>>>()
			.LearnType<float, FloatSerializationStrategy>()
			.LearnType<std::string, StringSerializationStrategy>()
			.SetFormat(SerializationFormat::Short)
		.Build();

		return serializer;
	}
}