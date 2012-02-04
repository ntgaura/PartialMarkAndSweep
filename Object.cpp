#include "Object.h"

#include <list>
#include <string>

namespace Shiracha
{
	namespace System
	{
		void CollectRoots();
		void MarkRoots();
		void ScanRoots();

		static std::list<Object*> rootset;
		typedef std::list<Object*>::iterator RootIter;

		Object::Object(std::string name)
			:	refcount(0),
				color(OBJECTCOLOR_BLACK),
				isBuffered(false),
				name(name)
		{ }

		Object::~Object()
		{
			std::cout << "Released: " << this->name << std::endl;
		}

		void Object::PushChild(Object* op)
		{
			op->Increment();
			this->children.push_back(op);
		}

		void Object::Increment()
		{
			++(this->refcount);
			this->color = OBJECTCOLOR_BLACK;
		}

		void Object::Decrement()
		{
			--(this->refcount);
			if( this->refcount == 0 )
			{
				this->Release();
			} else 
			{
				this->PossibleRoot();
			}
		}

		void Object::Release()
		{
			for(
				ChildIter now = this->children.begin();
				now != this->children.end();
				++now
			)
			{
				(*now)->Decrement();
			}
			this->color = OBJECTCOLOR_BLACK;
			if( !this->isBuffered )
			{
				delete this;
			}
		}

		void Object::PossibleRoot()
		{
			if( this->color != OBJECTCOLOR_PURPLE )
			{
				this->color = OBJECTCOLOR_PURPLE;
				if( !this->isBuffered )
				{
					this->isBuffered = true;
					rootset.push_back( this );
				}
			}
		}

		void CollectCycles()
		{
			MarkRoots();
			ScanRoots();
			CollectRoots();
		}

		void  MarkRoots()
		{
			RootIter now = rootset.begin();
			while ( now != rootset.end() )
			{
				if( (*now)->color == OBJECTCOLOR_PURPLE )
				{
					(*now)->MarkGray();
					++now;
					continue;
				} else
				{
					(*now)->isBuffered = false;
					Object* tmp = *now;
					now = rootset.erase( now );
					if(
						( tmp->color == OBJECTCOLOR_BLACK ) &&
						( tmp->refcount == 0 )
					)
					{
						delete tmp;
					}
					if( now == rootset.end() ) break;
				}
			}
		}

		void ScanRoots()
		{
			for(
				RootIter now = rootset.begin();
				now != rootset.end();
				++now
			)
			{
				(*now)->Scan();
			}
		}

		void CollectRoots()
		{
			RootIter now = rootset.begin();
			while ( now != rootset.end() )
			{
				Object* tmp = *now;
				now = rootset.erase( now );
				tmp->isBuffered = false;
				tmp->CollectWhite();
				if( now == rootset.end() ) break;
			}
		}

		void Object::MarkGray()
		{
			if( this->color != OBJECTCOLOR_GRAY )
			{
				this->color = OBJECTCOLOR_GRAY;
				for(
					ChildIter now = this->children.begin();
					now != this->children.end();
					++now
				)
				{
					--((*now)->refcount);
					(*now)->MarkGray();
				}
			}
		}

		void Object::Scan()
		{
			if( this->color == OBJECTCOLOR_GRAY )
			{
				if( this->refcount > 0 )
				{
					this->ScanBlack();
				} else
				{
					this->color = OBJECTCOLOR_WHITE;
					for(
						ChildIter now = this->children.begin();
						now != this->children.end();
						++now
					)
					{
						(*now)->Scan();
					}
				}
			}
		}

		void Object::ScanBlack()
		{
			this->color = OBJECTCOLOR_BLACK;
			for(
				ChildIter now = this->children.begin();
				now != this->children.end();
				++now
			)
			{
				++((*now)->refcount);
				if( (*now)->color != OBJECTCOLOR_BLACK )
				{
					(*now)->ScanBlack();
				}
			}
		}

		void Object::CollectWhite()
		{
			if(
				this->color == OBJECTCOLOR_WHITE &&
				!this->isBuffered
			)
			{
				this->color = OBJECTCOLOR_BLACK;
				for(
					ChildIter now = this->children.begin();
					now != this->children.end();
					++now
				)
				{
					(*now)->CollectWhite();
				}

				delete this;
			}
		}
	}
}

