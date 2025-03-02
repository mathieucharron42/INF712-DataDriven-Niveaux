#pragma once

#include "BytecodeData.h"
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
			.Add<std::optional<float>>("optional<float>")
			.BeginType<BytecodeInstruction>("BytecodeInstruction")
				.RegisterValue(BytecodeInstruction::Add, "Add")
				.RegisterValue(BytecodeInstruction::Divide, "Divide")
				.RegisterValue(BytecodeInstruction::Multiply, "Multiply")
				.RegisterValue(BytecodeInstruction::Pop, "Pop")
				.RegisterValue(BytecodeInstruction::Push, "Push")
				.RegisterValue(BytecodeInstruction::Peek, "Peek")
				.RegisterValue(BytecodeInstruction::Duplicate, "Duplicate")
				.RegisterValue(BytecodeInstruction::Substract, "Substract")
				.RegisterValue(BytecodeInstruction::Equals, "Equals")
				.RegisterValue(BytecodeInstruction::JumpIf, "JumpIf")
				.RegisterValue(BytecodeInstruction::Swap, "Swap")
			.EndType<BytecodeInstruction>()
			.BeginType<BytecodeData>("BytecodeData")
				.RegisterMember(&BytecodeData::Instruction, "Instruction")
				.RegisterMember(&BytecodeData::Value, "Value")
			.EndType<BytecodeData>()
			.Add<std::vector<BytecodeData>>("vector<BytecodeData>")
			.BeginType<GlobalTaxData>("GlobalTaxData")
			.RegisterMember(&GlobalTaxData::ComputationFunction, "ComputationFunction")
			.EndType<GlobalTaxData>()
		.Build();

		Serialization::Serializer serializer = Serialization::SerializerFactory(typeLibrary)
			.LearnType<float, Serialization::FloatSerializationStrategy>()
			.LearnType<std::string, Serialization::StringSerializationStrategy>()
			.LearnType<int, Serialization::Int32SerializationStrategy>()
			.LearnType<std::optional<float>, OptionalSerializationStrategy<std::optional<float>>>()
			.LearnType<BytecodeData, Serialization::ObjectSerializationStrategy<BytecodeData>>()
			.LearnType<std::vector<BytecodeData>, Serialization::VectorSerializationStrategy<std::vector<BytecodeData>>>()
			.LearnType<BytecodeInstruction, Serialization::EnumSerializationStrategy<BytecodeInstruction>>()
			.LearnType<GlobalTaxData, Serialization::ObjectSerializationStrategy<GlobalTaxData>>()
			.SetFormat(Serialization::SerializationFormat::Short)
		.Build();

		return serializer;
	}
}