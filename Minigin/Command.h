#pragma once

namespace RamCoreEngine
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Start() {};
		virtual void Execute() = 0;
	};

}

