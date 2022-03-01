#pragma once

#include <optional>

enum class BytecodeInstruction
{
	Push,
	Pop,
	Peek,
	Duplicate,
	Equals,
	Not,
	Jump,
	JumpIf,
	Add,
	Substract,
	Multiply,
	Divide,
	Swap,
};

struct BytecodeData
{
	BytecodeInstruction Instruction;
	std::optional<float> Value;
};