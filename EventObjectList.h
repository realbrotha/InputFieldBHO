#pragma once

#include "EventObject.h"

typedef struct CEventObject_Node
{
	CEventObject * pCEventObject;
	CEventObject_Node *pstrNext;
	CEventObject_Node *pstrCur;
	CEventObject_Node *pstrHead;
}STRCEVENTNODE,*PSTRCEVENTNODE;


class CEventObjectList  
{

public:
	void Remove();
	void Add(CEventObject *p);

	CEventObjectList();
	virtual ~CEventObjectList();

	PSTRCEVENTNODE ObjectList;

};

