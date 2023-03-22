//The build of the struct and the functios CreateAdptArray and SetAdptArrayAt and DeleteAdptArray were taken fron Q4 ifrom the test
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;

}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}
    if ((pArr->pElemArr)[idx] != NULL)
    {
	    pArr->delFunc((pArr->pElemArr)[idx]);
    }
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if ((pArr->pElemArr)[i] != NULL)
        {
		    pArr->delFunc((pArr->pElemArr)[i]);
	
        }
    }
	free(pArr->pElemArr);
	free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int ind) {
    if (pArr == NULL || ind < 0 || ind >= pArr->ArrSize || pArr->pElemArr[ind] == NULL) return NULL;
    return pArr->copyFunc(pArr->pElemArr[ind]);
};

int GetAdptArraySize(PAdptArray pArr){
    if(!pArr)
    {
        return -1;
    }
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
	if (pArr == NULL)
	{
		return;
	}
	for (int i = 0 ; i < pArr->ArrSize ; ++i)
	{
		if(pArr->pElemArr[i] != NULL)
		{
			pArr->printFunc(pArr->pElemArr[i]);
		}
	}
}