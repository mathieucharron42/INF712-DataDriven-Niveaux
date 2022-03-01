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
			.Add<GlobalTaxData>("GlobalTaxData")
			.Add<std::string>("string")
			.Add<int>("int")
			.Add<BytecodeData>("BytecodeData")
			.Add<std::vector<BytecodeData>>("std::vector<BytecodeData>")
			.Add<BytecodeInstruction>("Instruction")
			.Add<std::optional<float>>("optional<float>")
		.Build();

		TypeDescriptor globalTaxDataDescriptor = TypeDescriptorFactory<GlobalTaxData>(typeLibrary)
			.RegisterMember(&GlobalTaxData::ComputationFunction, "ComputationFunction")
		.Build();

		TypeDescriptor bytecodeInstructionDescriptor = TypeDescriptorFactory<BytecodeInstruction>(typeLibrary)
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
		.Build();

		TypeDescriptor bytecodeDataDescriptor = TypeDescriptorFactory<BytecodeData>(typeLibrary)
			.RegisterMember(&BytecodeData::Instruction, "Instruction")
			.RegisterMember(&BytecodeData::Value, "Value")
		.Build();

		Serializer serializer = SerializerFactory(typeLibrary)
			.LearnType<GlobalTaxData, ObjectSerializationStrategy<GlobalTaxData>>(globalTaxDataDescriptor)
			.LearnType<float, FloatSerializationStrategy>()
			.LearnType<std::string, StringSerializationStrategy>()
			.LearnType<int, Int32SerializationStrategy>()
			.SetFormat(SerializationFormat::Short)
			.LearnType<std::vector<BytecodeData>, VectorSerializationStrategy<std::vector<BytecodeData>>>()
			.LearnType<BytecodeData, ObjectSerializationStrategy<BytecodeData>>(bytecodeDataDescriptor)
			.LearnType<BytecodeInstruction, EnumSerializationStrategy<BytecodeInstruction>>(bytecodeInstructionDescriptor)
			.LearnType<std::optional<float>, OptionalSerializationStrategy<std::optional<float>>>()
		.Build();

		return serializer;
	}
}