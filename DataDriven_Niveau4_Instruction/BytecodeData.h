#pragma once

#include <optional>

enum class BytecodeInstruction
{
	Push,
	Pop,
	Add,
	Substract,
	Multiply,
	Divide
};

struct BytecodeData
{
	BytecodeInstruction Instruction;
	float Value;
};