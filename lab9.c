#include <stdio.h>
#include <stdlib.h>

#define Hash_size 10

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Fill out this structure
struct HashType
{
    struct RecordType** hashTable;
    int count;
};

// Compute the hash function
int hash(int x)
{
    return x % Hash_size;
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);

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

// Prints the records
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

// Display records in the hash structure
// Skip the indices which are free
// The output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
    int i, j;
    struct RecordType* pRecord;

    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);

        if (pHashArray->count > 0 && *(pHashArray->hashTable + i) != NULL) {
            for (j = 0; j < pHashArray->count; ++j){
                pRecord = *(pHashArray->hashTable + i) + j;

                if (pRecord != NULL){
                    printf(" %d, %c, %d ->", pRecord->id, pRecord->name, pRecord->order);
                }
            }
        }

        printf("\n");
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation
}
