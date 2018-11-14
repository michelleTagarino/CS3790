/*
	Author: Michelle Tagarino ID# 5029967
	Assignment #4: Memory Management (Final Assignment)
	Purpose: This file simulates memory allocation using priority queues.
*/

#include "memory.h"

/*
	Returns true if there was enough memory to allocate a memory request, false otherwise.
*/
bool FindFreeMemory(FREE &freeList, int size)
{
	FREE tmp;
	while (!freeList.empty() ) {
		if (freeList.top().hole.size >= size) {
			return true;
			break;
		}
		tmp.push(freeList.top() );
		freeList.pop();
	} 
	while (!tmp.empty() ) {
		freeList.push(tmp.top() );
		tmp.pop();
	}
	return false;
}

/*
	Inserts an expired alloc node into the free node list.
*/
void InsertFreeNode(FREE &freeList, int start, int size)
{
	freeNode newNode = {{start,size}};
	freeList.push(newNode);
}

/*
	Inserts an alloc node in the alloc list.
*/
void InsertAllocNode(ALLOC &allocList, int start, int size, int lease)
{
	allocNode newNode = {{start, size}, lease};
	allocList.push(newNode);
}

/*
	Checks if an alloc node's lease time has expired.
*/
bool CheckLease(ALLOC &allocList, long clock)
{
	if (!allocList.empty() && allocList.top().leaseExpiry == clock)
		return true;
	else return false;
}

/*
	Removes free memory when memory request is successful.
*/
void RemoveFree(FREE &freeList, int size)
{
	freeNode newNode = {{freeList.top().hole.start + size, freeList.top().hole.size - size}};
	freeList.pop();				
	freeList.push(newNode);
}

/*
	Removes an alloc node from the alloc list (it will have an expired lease time).
*/
void RemoveAlloc(ALLOC &allocList)
{
	allocList.pop();
}

/*
	Returns true if merge between adjacent memory blocks was successful, false otherwise.
*/
bool MergeMemory(FREE &freeList, int size)
{
	FREE tmp;
	bool memoryMerged = false;

	while (!freeList.empty() ) {
		tmp.push(freeList.top() );
		freeList.pop();

		if (freeList.top().hole.start == (tmp.top().hole.start+tmp.top().hole.size) ) { //make sure the holes are adjecent
			if ((tmp.top().hole.size + freeList.top().hole.size) >= size) { //check if the combined size is big enough
				freeNode newNode = {{tmp.top().hole.start,tmp.top().hole.size + freeList.top().hole.size}};
				freeList.pop();
				freeList.push(newNode);
				tmp.pop();
				memoryMerged = true;
				break;
			}
			else memoryMerged = false;
		} 
	}
	while (!tmp.empty() ) {
		freeList.push(tmp.top() );
		tmp.pop();
	}
	return memoryMerged;
}
