#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

				std::string mainStr = "";
				int length = k.length();

				//filtering given parameter 
				for(int x = 0; x < length; x++){
					char currentChar = k[x];
						if(std::isdigit(currentChar)){
							mainStr += currentChar;
						}

						else if(std::isalpha(currentChar)){
							mainStr += currentChar;
						}
				}

				int filteredLength = mainStr.length();

				//splitting into 6 groups
				HASH_INDEX_T word[5];

				for(int x = 0; x < 5; x++){
					word[x] = 0;
				}


				//hashing

				int indexSplit = 4;
				for(int x = filteredLength; x > 0 && indexSplit >= 0; x-=6){

					HASH_INDEX_T val = 0;

					int splitStart = x-6; 		//account for splits smaller than 6
					if(splitStart < 0){
						splitStart = 0;
					}

					// hashing operation (powers of 36)

					for(int y = splitStart; y < x; y++){

						char current = mainStr[y];
						HASH_INDEX_T currentVal = letterDigitToNumber(current);
						val = val * 36 + currentVal;

					}

					word[indexSplit] = val;
					indexSplit--;
				}

			//combining the 6 parts 

			HASH_INDEX_T finished_product = 0;

			for(int x = 0; x < 5; x++){
				finished_product += rValues[x] * word[x];
			}


			return finished_product;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

				bool varifiedLetter = std::isalpha(letter);
				bool varifiedDigit = std::isdigit(letter);

				if(varifiedLetter){
					char lowercase = std::tolower(letter);
					return static_cast<HASH_INDEX_T>(lowercase - 'a');
				}

				else if(varifiedDigit){
					return static_cast<HASH_INDEX_T>((letter - '0')+26);
				}
	

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
