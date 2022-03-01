#pragma once

#include "BytecodeData.h"

#include <stack>
#include <cassert>
#include <optional>
#include <vector>

class VM
{
public:
	using value_t = float;

	VM()
		: _stack()
	{ }

	std::optional<value_t> Execute(const std::vector<BytecodeData>& bytecodes, value_t parameter)
	{
		std::vector<value_t> params = {parameter};
		return Execute(bytecodes, params);
	}

	std::optional<value_t> Execute(const std::vector<BytecodeData>& bytecodes, std::vector<value_t> parameters)
	{
		std::optional<value_t> output;

		InitializeStack(parameters);

		for (_instructionPtr = bytecodes.begin(); _instructionPtr != bytecodes.end(); ++_instructionPtr)
		{
			const BytecodeData& bytecode = *_instructionPtr;
			output = Execute(bytecode);
		}
		
		return output;
	}

private:
	void InitializeStack(std::vector<value_t> parameters)
	{
		// Initialize stack in reverse order for convenience
		for (std::vector<value_t>::reverse_iterator it = parameters.rbegin(); it != parameters.rend(); ++it)
		{
			const value_t& param = *it;
			Push(param);
		}
	}

	std::optional<value_t> Execute(const BytecodeData& bytecode)
	{
		std::optional<value_t> output;

		if (bytecode.Instruction == BytecodeInstruction::Add)
		{
			value_t v1 = Pop();
			value_t v2 = Pop();
			Push(v2 + v1);
		}
		else if (bytecode.Instruction == BytecodeInstruction::Substract)
		{
			value_t v1 = Pop();
			value_t v2 = Pop();
			Push(v2 - v1);
		}
		else if (bytecode.Instruction == BytecodeInstruction::Multiply)
		{
			value_t v1 = Pop();
			value_t v2 = Pop();
			Push(v2 * v1);
		}
		else if (bytecode.Instruction == BytecodeInstruction::Divide)
		{
			value_t v1 = Pop();
			value_t v2 = Pop();
			Push(v2 / v1);
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
		else if (bytecode.Instruction == BytecodeInstruction::Peek)
		{
			output = Peek();
		}
		else if (bytecode.Instruction == BytecodeInstruction::Duplicate)
		{
			Push(Peek());
		}
		else if (bytecode.Instruction == BytecodeInstruction::Equals)
		{
			value_t value1 = Pop();
			value_t value2 = Pop();
			Push(value2 == value1);
		}
		else if (bytecode.Instruction == BytecodeInstruction::Not)
		{
			bool value = static_cast<bool>(Pop());
			Push(!value);
		}
		else if (bytecode.Instruction == BytecodeInstruction::JumpIf)
		{
			ensure(bytecode.Value.has_value());
			bool eval = static_cast<bool>(Pop());
			if (eval)
			{
				int nbInstructions = static_cast<int>(bytecode.Value.value());
				Jump(nbInstructions);
			}
		}
		else if (bytecode.Instruction == BytecodeInstruction::Jump)
		{
			ensure(bytecode.Value.has_value());
			int nbInstructions = static_cast<int>(bytecode.Value.value());
			Jump(nbInstructions);
		}
		else if (bytecode.Instruction == BytecodeInstruction::Swap)
		{
			value_t value1 = Pop();
			value_t value2 = Pop();
			Push(value1);
			Push(value2);
		}
		else
		{
			assert(false && "Unsupported instruction");
		}
		return output;
	}

	void Jump(int nbInstructions)
	{
		_instructionPtr += 2;
	}

	value_t Pop()
	{
		value_t value = Peek();
		_stack.pop();
		return value;
	}

	value_t Peek()
	{
		value_t value = _stack.top();
		return value;
	}

	void Push(value_t value)
	{
		_stack.push(value);
	}

	std::stack<value_t> _stack;
	std::vector<BytecodeData>::const_iterator _instructionPtr;
};
