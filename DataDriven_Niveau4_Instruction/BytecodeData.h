#pragma once

#include <optional>

enum class BytecodeInstruction
{
	Push,
	Pop,
	Peek,
	Duplicate,
	Add,
	Substract,
	Multiply,
	Divide,
};

struct BytecodeData
{
	BytecodeInstruction Instruction;
	std::optional<float> Value;
};