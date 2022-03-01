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
		.Build();

		TypeDescriptor globalTaxDataDescriptor = TypeDescriptorFactory<GlobalTaxData>(typeLibrary)
			.RegisterMember(&GlobalTaxData::TPS, "TPS")
			.RegisterMember(&GlobalTaxData::TVQ, "TVQ")
			.RegisterMember(&GlobalTaxData::EHF, "EHF")
		.Build();

		Serializer serializer = SerializerFactory(typeLibrary)
			.LearnType<GlobalTaxData, ObjectSerializationStrategy<GlobalTaxData>>(globalTaxDataDescriptor)
			.LearnType<float, FloatSerializationStrategy>()
			.SetFormat(SerializationFormat::Short)
		.Build();

		return serializer;
	}
}