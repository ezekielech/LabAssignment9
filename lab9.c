#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* pData;
}

// Compute the hash function
int hash(int x)
{
	return x % MAX_SIZE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	printf("\nHash Table: \n");
	for (i=0;i<hashSz;++i)
	{
		if (pHashArray[i].pData != NULL)
		{
			printf("Index %d -> %d %c %d\n", i, pHashArray[i].pData -> id, pHashArray[i].pData -> name, pHashArray[i].pData -> order);
		}
		// if index is occupied with any records, print all
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType hashTable[MAX_SIZE] = {0};
	for (int i = 0; i < recordSz; i++)
	{
		int index = hash(pRecords[i].id);
		while (hashTable[index].pData != NULL) {
			index = (index + 1) % MAX_SIZE;
		}
		hashTable[index].pData = &pRecords[i];
	}

	displayRecordsInHash (hashTable, MAX_SIZE);

	free(pRecords);
}