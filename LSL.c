/* Lab Exam WS 2019 (Software Construction 1) */
#define _CRT_SECURE_NO_WARNINGS

// include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int characters;
	int words;
	int sentences;
	int syllables;
	int readability;
}
properties;

// function prototypes
void printTextProperties(properties);
int getCharacterCount(char *text, char character);
int getNumberOfWords(char *text);
int getNumberOfSentences(char *text);
int getNumberOfSyllablesInWord(char *word);
int getNumberOfSyllables(char *text);
properties getTextProperties(char *text);
int getStringSize(char *string);
char* copyString(char* original);

// Main function
int main(void) 
{
	// Simple sentences
	char easy[] = "No one said; it would. be easy! AaEe IiOoUu?";
	
	// William Lyon Phelps: The Pleasure of Books
	char bookSpeech [] =  
	"A borrowed book is like a guest in the house; it must be treated with punctiliousness, with a certain considerate formality. "
	"You must see that it sustains no damage; it must not suffer while under your roof. "
	"You cannot leave it carelessly, you cannot mark it, you cannot turn down the pages, you cannot use it familiarly. "
	"And then, some day, although this is seldom done, you really ought to return it.";
	
	
	//To determine text properties
	properties easyProperties = getTextProperties(easy);
	properties bookProperties = getTextProperties(bookSpeech);
	
	//To display results
	printf ("\nTest string \"%s\":\n", easy);
	printTextProperties(easyProperties);
	
	printf("\nWilliam Lyon Phelps, The Pleasure of Books:\n");
	printTextProperties(bookProperties);
	
	getchar();
	return 0;
	
}

/* Print properties to the console */
void printTextProperties(properties textProperties) 
{
	printf("Characters : %d\n", textProperties.characters);
	printf("Words : %d\n", textProperties.words);
	printf("Sentences : %d\n", textProperties.sentences);
	printf("Syllables : %d\n", textProperties.syllables);
	printf("Readability : %.1d out of 100\n", textProperties.readability);
}

int getCharacterCount(char *text, char character)
{
	int charCount = 0;
	int element = 0;
	
	while (text[element] != '\0')
		if (text[element++] == character)
			charCount++;
		return charCount;
}

int getNumberOfWords(char *text)
{
	// Add +1 to include first word
	return (getCharacterCount(text, ' ') + 1);
}

int getNumberOfSentences(char *text)
{
	int sentenceCount = 0;
	sentenceCount += getCharacterCount(text, '.');
	sentenceCount += getCharacterCount(text, ';');
	sentenceCount += getCharacterCount(text, '!');
	sentenceCount += getCharacterCount(text, '?');
	
	return sentenceCount;
}

int getNumberOfSyllablesInWord(char *word)
{
	int syllableCount = 0;
	if (strlen(word) < 4)
		return 1;
	
	syllableCount += getCharacterCount(word, 'a');
	syllableCount += getCharacterCount(word, 'e');
	syllableCount += getCharacterCount(word, 'i');
	syllableCount += getCharacterCount(word, 'o');
	syllableCount += getCharacterCount(word, 'u');
	syllableCount += getCharacterCount(word, 'A');
	syllableCount += getCharacterCount(word, 'E');
	syllableCount += getCharacterCount(word, 'I');
	syllableCount += getCharacterCount(word, 'O');
	syllableCount += getCharacterCount(word, 'U');
	
	return syllableCount;
}

int getNumberOfSyllables(char *text)
{
	char* copy = copyString(text);
	char* copyStart = copy;
	int wordCount = getNumberOfWords(text);
	int syllables = 0;
	int element;
	
	while (1)
	{
		//Stop counting syllables when no more words
		if (strtok(copy, " ") == NULL)
			break;
		
		syllables += getNumberOfSyllablesInWord(copy);
		
		//Move the pointer for copy to the beginning of the rest of the phrase
		element = 0;
		while (1)
		{
			if (copy[element++] == '\0')
				break;
		}
		copy = &copy[element];
		
		continue;
	}
	
	//free allocated memory
	free(copyStart);
	
	return syllables;
	
}

properties getTextProperties(char *text)
{
	properties textStats;
	
	textStats.characters = (int)strlen(text);
	textStats.words = getNumberOfWords(text);
	textStats.sentences = getNumberOfSentences(text);
	textStats.syllables = getNumberOfSyllables(text);
	textStats.readability = 206.835 - 1.015 * textStats.words / textStats.sentences - 84.6 * textStats.syllables / textStats.words;
	
	return textStats;
}

int getStringSize(char *string)
{
	int characterCount = 0;
	
	while (string[characterCount] != '\0')
		characterCount++;
	
	return characterCount + 1;

}

char* copyString(char* original)
{
	int stringSize = getStringSize(original);
	char* copy;
	
	if( ( copy = (char*)malloc(stringSize * sizeof(char)) ) == NULL)
		exit (EXIT_FAILURE);
	
	for (int i = 0; i < stringSize; i++)
		copy[i] = original[i];
	
	return copy;
}
