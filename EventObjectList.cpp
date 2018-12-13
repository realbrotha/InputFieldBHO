#include "stdafx.h"
#include "EventObjectList.h"

CEventObjectList::CEventObjectList()
{
	ObjectList = NULL;
}

CEventObjectList::~CEventObjectList()
{
	if (ObjectList != NULL)
	{
		Remove();
	}
	
}

void CEventObjectList::Add(CEventObject *p)
{
	CEventObject_Node *NewNode = new CEventObject_Node;
	NewNode->pCEventObject = p;
	NewNode->pstrNext = NULL;

	if (ObjectList == NULL)
	{
		ObjectList = NewNode;
		ObjectList->pstrHead = NewNode;
		ObjectList->pstrCur = NewNode;
	}

	else
	{
		ObjectList->pstrCur->pstrNext = NewNode;
		ObjectList->pstrCur = ObjectList->pstrCur->pstrNext;
	}

	return;
}

void CEventObjectList::Remove()
{
	if (ObjectList == NULL)
	{
		return;
	}
	if (ObjectList->pstrHead == NULL)
	{
		return;
	}
	while (ObjectList->pstrHead != NULL)
	{
		delete ObjectList->pstrHead->pCEventObject;
		CEventObject_Node *DelNode = ObjectList->pstrHead;
		
		ObjectList->pstrHead = ObjectList->pstrHead->pstrNext;
		
		delete DelNode;
	}

}
