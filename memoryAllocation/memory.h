/*
	Author: Michelle Tagarino
	Purpose: Header file for Memory Simulation (Assignment #4)
*/

#ifndef MEMORY
#define MEMORY

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <time.h>

using namespace std;

const int MIN_LEASE = 40; 
const int MAX_LEASE = 100;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 1000;
const int MEMORY_SIZE = 1000;
const int REQUEST_INTERVAL = 10;

struct range {
	int start; // starting address of the range
	int size;  // size of the range 
};

struct freeNode {
	struct range hole;
};

struct allocNode {
	struct range allocated;
	int leaseExpiry;
};

/* This will sort the free list in ascending order by start location */
struct compareFree {
	bool operator()(freeNode &A, freeNode &B) {
		return A.hole.start > B.hole.start;
	}
};

/* This will sort the alloc list in ascending order by lease expiry time */
struct compareAlloc {
	bool operator()(allocNode &A, allocNode &B) {
		return A.leaseExpiry > B.leaseExpiry;
	}
};

typedef priority_queue< freeNode, vector<freeNode>,compareFree > FREE;
typedef priority_queue< allocNode, vector<allocNode>,compareAlloc > ALLOC;

bool FindFreeMemory(FREE&, int); //Returns true if enough free memory, false otherwise.
void InsertFreeNode(FREE&, int, int); //Inserts expired alloc node back into free memory list.
void InsertAllocNode(ALLOC&, int, int, int); //Inserts alloc when memory request successful.
bool CheckLease(ALLOC&, long); //Returns true if any alloc nodes' lease times have expired, false otherwise.
void RemoveFree(FREE&, int); //Removes free memory when memory request was successful.
void RemoveAlloc(ALLOC&); //Removes alloc from list when its lease expired.
bool MergeMemory(FREE&, int); //Returns true if memory merging was successful, false otherwise. 
void dump();

#endif
