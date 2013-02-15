
#include <stdio.h>
#include <stdlib.h>

struct PrimeNumber
{
   int index;
   int value;
   struct PrimeNumber *next;
};

void printPrimeNumber(struct PrimeNumber *primeNumberPointer);
struct PrimeNumber *getPrimeNumberPointer(int index, int value);
int isPrime(int candidatePrime, struct PrimeNumber *primePointer);

int main()
{
   struct PrimeNumber *headPointer = getPrimeNumberPointer(1, 2);
   struct PrimeNumber *tailPointer = headPointer;
   
   int currentIndex = 1;
   int currentCandidate = 3;
   
   while(currentIndex < 100)
   {
      int isCandidatePrime = isPrime(currentCandidate, headPointer);
      if(isCandidatePrime == 1)
      {
         currentIndex++;
         struct PrimeNumber *newPrimeNumber = getPrimeNumberPointer(currentIndex, currentCandidate);
         tailPointer->next = newPrimeNumber;
         tailPointer = newPrimeNumber;
      }
      currentCandidate += 2;
   }
   
   printPrimeNumber(headPointer);
   return 0;
}

// *****************************************************************************
// Creates a new PrimeNumber structure with the initial values.
// *****************************************************************************

struct PrimeNumber *getPrimeNumberPointer(int index, int value)
{
   struct PrimeNumber *primeNumberPointer = (struct PrimeNumber *) malloc(sizeof(struct PrimeNumber));
   primeNumberPointer->index = index;
   primeNumberPointer->value = value;
   return primeNumberPointer;
}

// *****************************************************************************
// Prints a PrimeNumber structure.
// *****************************************************************************

void printPrimeNumber(struct PrimeNumber *primeNumberPointer)
{
   printf("Prime number : index = %d, value = %d\n", primeNumberPointer->index, primeNumberPointer->value);
   if(primeNumberPointer->next != NULL)
   {
      printPrimeNumber(primeNumberPointer->next);
   }
}

// *****************************************************************************
// Tests if a number is prime.
// *****************************************************************************

int isPrime(int candidatePrime, struct PrimeNumber *primePointer)
{
   while(1)
   {
      if(primePointer == NULL)
      {
         return 1;
      }
      else if(candidatePrime % primePointer-> value == 0)
      {
         return 0;
      }
      primePointer = primePointer->next;
   }
}
