#pragma once

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Start() = 0;
		virtual void Execute() = 0;
	};

}

