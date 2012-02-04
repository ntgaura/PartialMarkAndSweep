#ifndef SHIRACHA_OBJECT_H__
#define SHIRACHA_OBJECT_H__

#include <list>
#include <iostream>
#include <string>

namespace Shiracha
{
	namespace System
	{
		enum ObjectColor
		{
			OBJECTCOLOR_WHITE = 0,
			OBJECTCOLOR_BLACK = 1,
			OBJECTCOLOR_GRAY = 2,
			OBJECTCOLOR_PURPLE = 3,
		};

		// 循環参照を生成しているオブジェクトを開放
		void CollectCycles();

		class Object
		{
			friend void CollectRoots();
			friend void MarkRoots();
			friend void ScanRoots();
			public:
				std::string name;
				Object(std::string name);
				virtual ~Object();

				void PushChild(Object* op);

				void Increment();
				void Decrement();
			private:
				std::list<Object*> children;
				typedef std::list<Object*>::iterator ChildIter;
				int refcount;
				bool isBuffered;
				ObjectColor color;

				void Release();
				void PossibleRoot();
				void MarkGray();
				void Scan();
				void ScanBlack();
				void CollectWhite();
		};
	}
}

#endif	// SHIRACHA_OBJECT_H__

