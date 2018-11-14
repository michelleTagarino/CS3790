/*
	Author: Michelle Tagarino ID# 5029967
	Assignment #4: Memory Management (Final Assignment)
	Purpose: This file tests the memory.cpp file. It prints out the memory simulation analysis.
*/

#include "memory.h"

int size,lease; // Used to hold the randomly generated block sizes and leases
int total_requests = 0; // Total number of requests
int satisfied_requests = 0; // Number of satisfied requests
int unsatisfied_requests = 0; // Number of unsatisfied requests

vector<int> block_sizes; // Holds all the block sizes
int smallest_blocksize  = MAX_SIZE; // Smallest block size
int largest_blocksize   = 0; // Longest block size
float average_blocksize = 0; // Average block size

vector<int> lease_expiries; // Holds all the leases
int shortest_lease  = MAX_LEASE; // Shortest lease duration
int longest_lease   = 0; // Longest lease duration
float average_lease = 0; // Average lease duration

int num_merges = 0; // Total number of merges performed

FREE freeList;
ALLOC allocList;

int main ()
{
	srand(time(NULL));
	
	freeNode newFree = {{0,1000}};
	freeList.push(newFree);

	long clock = 0;

	do {

		if (clock % REQUEST_INTERVAL == 0) {
			/* generate a memory request */
			total_requests++;
			size  = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
			block_sizes.push_back(size);
			if (size < smallest_blocksize) smallest_blocksize = size; //determine smallest block size
			if (size > largest_blocksize ) largest_blocksize  = size; //determine largest block size

			lease = (rand() % (MAX_LEASE - MIN_LEASE) + MIN_LEASE) + clock;
			lease_expiries.push_back(lease);
			if (lease < shortest_lease) shortest_lease = lease; //determine shortest lease time
			if (lease > longest_lease ) longest_lease  = lease; //determine longest lease time
			
			//merge small blocks of memory if not enough memory left
			if ( !FindFreeMemory(freeList,size) ) {
				if (MergeMemory(freeList,size) ) num_merges++;
				else unsatisfied_requests++;
			}
			//if enough free memory left, add alloc node and remove corresponding free memory from list
			if (FindFreeMemory(freeList,size)) {
				satisfied_requests++;
				RemoveFree(freeList,size);
				InsertAllocNode(allocList, freeList.top().hole.start-size, size, lease);
			}
		}
		/* see if lease has expired  */
		while (CheckLease(allocList,clock) ) {
			InsertFreeNode(freeList,allocList.top().allocated.start, allocList.top().allocated.size);
			RemoveAlloc(allocList);			
		}

	} while (++clock < TIME_LIMIT);
	
	dump();

	return 0;
}

/*
	dumps the report of the simulation.
*/
void dump() {

	printf("Request Analysis:\n");
	printf("-------------------------------------\n");
	printf("Total Number of Requests:       %5d\n", total_requests);
	printf("Number of Satisfied Requests:   %5d\n", satisfied_requests);
	printf("Number of Unsatisfied Requests: %5d\n\n", unsatisfied_requests);
	
	//calculate the average of the lease expiries
	float sum_blocks = 0; // sum of block sizes
	for (int i=0; i<block_sizes.size(); i++) {
		sum_blocks += block_sizes[i];
	}
	average_blocksize = sum_blocks / block_sizes.size();

	printf("Block Size Analysis:\n");
	printf("-------------------------------------\n");
	printf("Smallest Block Size: %16d\n", smallest_blocksize);
	printf("Largest Block Size :  %15d\n", largest_blocksize);
	printf("Average Block Size :  %15.2f\n\n", average_blocksize);

	//calculate the average of the lease expiries
	float sum_leases = 0; // sum of lease expiries
	for (int i=0; i<lease_expiries.size(); i++) {
		sum_leases += lease_expiries[i];
	}
	average_lease = sum_leases / lease_expiries.size();

	printf("Lease Duration Analysis:\n");
	printf("-------------------------------------\n");
	printf("Shortest Lease Duration: %12d\n", shortest_lease);
	printf("Longest Lease Duration :  %11d\n", longest_lease);
	printf("Average Lease Duration :  %11.2f\n\n", average_lease);

	printf("Memory Merge Analysis:\n");
	printf("-------------------------------------\n");
	printf("Total Number of Merges Performed:  %2d\n\n", num_merges);

	// Final state of the Free List
	printf("State of the Free List:\n");
	printf("-------------------------------------\n");
	printf("Node:     Start:     Size:\n");
	//print the free node values
	for (int i=1; !freeList.empty(); i++ ) {
	printf("%-9d %-10d %-9d\n", i, freeList.top().hole.start, freeList.top().hole.size);
		freeList.pop();
	}


	// Final state of the Allocated List
	printf("\nState of the Allocated List:\n");
	printf("-------------------------------------\n");
	
	// if the allocated list is empty (...and it should be)
	if (allocList.empty()) {
		cout << "The Allocated List is empty!\n";
	} else printf("Node:     Start:     Size:     Lease:\n");
	
	//print the alloc node values
	for (int i=1; !allocList.empty(); i++ ) {
	printf("%-9d %-10d %-9d %-13d\n", i, allocList.top().allocated.start, allocList.top().allocated.size, allocList.top().leaseExpiry);
		allocList.pop();
	}
}
