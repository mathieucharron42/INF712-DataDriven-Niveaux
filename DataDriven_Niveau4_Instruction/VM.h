#pragma once

#include "BytecodeData.h"

#include <stack>
#include <cassert>
#include <optional>
#include <vector>

class VM
{
public:
	VM()
		: _stack()
	{ }

	std::optional<float> Execute(std::vector<BytecodeData> code, float parameter)
	{
		std::vector<float> params = {parameter};
		return Execute(code, params);
	}

	std::optional<float> Execute(std::vector<BytecodeData> code, std::vector<float> parameters)
	{
		std::optional<float> output;

		InitializeStack(parameters);
		for(const BytecodeData& bytecode : code)
		{
			output = Execute(bytecode);
		}
		return output;
	}

	void InitializeStack(std::vector<float> parameters)
	{
		while (!_stack.empty())
		{
			_stack.pop();
		}
		
		for(float param : parameters)
		{
			Push(param);
		}
	}

	std::optional<float> Execute(const BytecodeData& bytecode)
	{
		std::optional<float> output;

		if (bytecode.Instruction == BytecodeInstruction::Add)
		{
			Push(Pop() + Pop());
		}
		else if (bytecode.Instruction == BytecodeInstruction::Substract)
		{
			Push(Pop() - Pop());
		}
		else if (bytecode.Instruction == BytecodeInstruction::Multiply)
		{
			Push(Pop() * Pop());
		}
		else if (bytecode.Instruction == BytecodeInstruction::Divide)
		{
			Push(Pop() / Pop());
		}
		else if (bytecode.Instruction == BytecodeInstruction::Push)
		{
			ensure(bytecode.Value.has_value());
			Push(bytecode.Value.value());
		}
		else if (bytecode.Instruction == BytecodeInstruction::Pop)
		{
			output = Pop();
		}
		else
		{
			assert(false && "Unsupported instruction");
		}
		return output;
	}

	float Pop()
	{
		float value = _stack.top();
		_stack.pop();
		return value;
	}

	void Push(float value)
	{
		_stack.push(value);
	}

	std::stack<float> _stack;
};
