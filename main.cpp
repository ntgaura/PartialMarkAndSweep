#include <iostream>
#include <string>
#include "Object.h"

using namespace Shiracha::System;

int main()
{
	// ���֥������Ȥ���
	Object *objA, *objB, *objC, *objD;
	objA = new Object("objA");
	objB = new Object("objB");
	objC = new Object("objC");
	objD = new Object("objD");

	// ľ�ܥ桼�������ɤ���äƤ���Τ�
	// objA��objD�Ȥ������Ȥˤ��ޤ��礦��
	objA->Increment();
	objD->Increment();

	// �۴Ļ��Ȥκ���
	objA->PushChild(objB);
	objB->PushChild(objC);
	objC->PushChild(objA);

	// objA�����Ȥ���ʤ��ʤä��Τǡ�
	// ��ν۴Ļ��Ȥϻ��Ȥ���ʤ��۴Ļ��Ȥˤʤä�
	objA->Decrement();

	// objD��¾��ï����⻲�Ȥ���Ƥ��ʤ��Τǡ�
	// ���ξ��¨���˲�������ޤ�
	objD->Decrement();

	// �۴Ļ��ȥ��֥������Ȥ�������
	// �����ȥ����Ȥ���ȡ�ABC���������ʤ������ǧ�Ǥ��ޤ�
	CollectCycles();

	return 0;
}
