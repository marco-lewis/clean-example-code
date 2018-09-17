#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void rotateString(char *string, int stringLength){
  char temp = string[0];

  for (int i = 0; i < stringLength - 1; i++){
    string[i] = string[i+1];
  }

  string[stringLength - 1] = temp;
}

void assignRotationsOfNumber(int currentNumber, int *rotationsOfNumber, int numberOfDigits){
  char numberString[numberOfDigits];

  sprintf(numberString, "%d", currentNumber);

  for (int i = 0; i < numberOfDigits; i++){
    rotateString(numberString, numberOfDigits);
    int rotatedNumber = atoi(numberString);
    rotationsOfNumber[i] = rotatedNumber;
  }
}

bool areAllRotationsOfNumbersPrime(int *numberArray, int arrayLength, bool *isPrime){
  bool allArePrime = true;
  int i = 0;

  while(i < arrayLength && allArePrime){
    int numberToCheck = numberArray[i];
    allArePrime = isPrime[numberToCheck];
    i++;
  }

  return allArePrime;
}

void setRotationsOfNumbersToTrue(int *numbers, int numberOfDigits, bool *isCyclicPrime){
  for (int j = 0; j < numberOfDigits; j++){
    int number = numbers[j];
    isCyclicPrime[number] = true;
  }
}

void assignCyclicPrimeForNumberAndRotations(int number, bool *isCyclicPrime, bool *isPrime){
  int numberOfDigits = (int) ceil(log10(number));

  if (numberOfDigits == 1){
    isCyclicPrime[number] = true;
  } else {
    int rotationsOfNumber[numberOfDigits - 1];
    assignRotationsOfNumber(number, rotationsOfNumber, numberOfDigits);

    if (areAllRotationsOfNumbersPrime(rotationsOfNumber, numberOfDigits, isPrime)) {
      setRotationsOfNumbersToTrue(rotationsOfNumber, numberOfDigits, isCyclicPrime);
      isCyclicPrime[number] = true;
    }
  }
}

int findNumberOfCyclicPrimes(bool *isPrime, bool *isCyclicPrime, int arraySize){
  int numberOfCyclicPrimes = 0;

  for (int number = 1; number < arraySize; number++){
    if(isPrime[number] && !isCyclicPrime[number]) assignCyclicPrimeForNumberAndRotations(number, isCyclicPrime, isPrime);
    if (isCyclicPrime[number]) numberOfCyclicPrimes += 1;
  }

  return numberOfCyclicPrimes;
}

void printResults(bool *isCyclicPrime, int arraySize, int numberOfCyclicPrimes){
  int cyclicCount = 1;
  printf("Cyclic Primes up to 1,000,000\n");
  for (int n = 1; n < arraySize; n++){
    if (isCyclicPrime[n]) printf("%i: %i\n", cyclicCount++, n);
  }

  printf("Number of cyclic primes: %d\n", numberOfCyclicPrimes);
}

void seivePrimes(bool *isPrime, int arraySize){
  memset(isPrime, true, arraySize);
  isPrime[0] = false;
  isPrime[1] = false;

  for (int j = 2; j < arraySize; j++){
    if(isPrime[j]){
      for (int k = 2; k*j < arraySize; k++){
        isPrime[k*j] = false;
      }
    }
  }
}

void initializeArrays(bool *isPrime, bool *isCyclicPrime, int arraySize){
  seivePrimes(isPrime, arraySize);
  memset(isCyclicPrime, false, arraySize);
}

void solve(){
  int arraySize = 1000000;
  bool *isPrime = malloc(arraySize * sizeof(bool));
  bool *isCyclicPrime = malloc(arraySize * sizeof(bool));

  initializeArrays(isPrime,isCyclicPrime,arraySize);

  int numberOfCyclicPrimes = findNumberOfCyclicPrimes(isPrime, isCyclicPrime, arraySize);

  printResults(isCyclicPrime, arraySize, numberOfCyclicPrimes);

  free(isPrime);
  free(isCyclicPrime);
}



int main(int argc, char* argv[]){
  solve();
  return 0;
}
