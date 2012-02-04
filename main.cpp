#include <iostream>
#include <string>
#include "Object.h"

using namespace Shiracha::System;

int main()
{
	// オブジェクトを作る
	Object *objA, *objB, *objC, *objD;
	objA = new Object("objA");
	objB = new Object("objB");
	objC = new Object("objC");
	objD = new Object("objD");

	// 直接ユーザコードがもっているのは
	// objAとobjDということにしましょう。
	objA->Increment();
	objD->Increment();

	// 循環参照の作成
	objA->PushChild(objB);
	objB->PushChild(objC);
	objC->PushChild(objA);

	// objAが参照されなくなったので、
	// 上の循環参照は参照されない循環参照になった
	objA->Decrement();

	// objDは他の誰からも参照されていないので、
	// この場で即時に解放されます
	objD->Decrement();

	// 循環参照オブジェクトを回収する
	// コメントアウトすると、ABCが回収されない事を確認できます
	CollectCycles();

	return 0;
}
