#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* SumCharsAndDigits(const char* str);
void PrintWordsSorted(const char* str);

/*
 * Test the SumCharsAndDigits function.
 * Aborts if the test fails.
 * Parameters:
 *     str: The SumCharsAndDigits argument.
 *     oracle: The string that should be returned by SumCharsAndDigits.
 */
void SumCharsAndDigitsTest(const char* str, const char* oracle);

/*
 * Add a number's digits together and return the sum.
 * Parameter:
 *     number: The number of which to compute the digit's sum.
 * Return:
 *     The sum of the given number's digits.
 */
int SumDigits(int number);

int main(int argc, char *argv[])
{
    SumCharsAndDigitsTest("123", "6");
	SumCharsAndDigitsTest("1d3", "8");
	SumCharsAndDigitsTest("1D3", "8");
	SumCharsAndDigitsTest("5#83", "7");
	/* 1 + 2 + 3 + 4 + 9 + 7 + 0 + 0 + 8 = 34 then 3 + 4 = 7 */
	SumCharsAndDigitsTest("aBcD97?\18", "7");
	/*
	 * 1 + 2 + 3 + 4 + 9 + 7 + 0 + 0 + 8 + 24 + 25 + 26 = 109
	 * then 1 + 0 + 9 = 10 then 1 + 0 = 1
	 */
	SumCharsAndDigitsTest("aBcD97?\18XYZ", "1");

	PrintWordsSorted("mon code est cool !");

	printf("All tests passed with success.\n");

	return EXIT_SUCCESS;
}

char* SumCharsAndDigits(const char* str)
{
	int sum = 0;
	char* sum_str = (char*)malloc(2 * sizeof(char));
	char c;
	int digits_sum;

	/* Check allocation succeeded */
	assert(sum_str != NULL);

	/* The sum's string is 1 character long. Mark its end. */
	sum_str[1] = '\0';

	while (*str != '\0') {
		c = *str;
		if (c >= 'a' && c <= 'z') {
			sum += c - 'a' + 1;
		} else if (c >= 'A' && c <= 'Z') {
			sum += c - 'A' + 1;
		} else if (c >= '0' && c <= '9') {
			sum += c - '0';
		}
		str++;
	}

	/* Add the sum's digits together */
	digits_sum = sum;
	do {
		digits_sum = SumDigits(digits_sum);
	} while (digits_sum >= 10);

	/* Return the sum's string representation */
	sum_str[0] = digits_sum + '0';

	return sum_str;
}

struct WordList
{
	char* word;
	int value;
	struct WordList* next;
};

void CreateWordList(struct WordList list)
{
	list.word = NULL;
	list.value = -1;
	list.next = NULL;
}

void InsertWordList(struct WordList list, const char* buffer, int value)
{
	struct WordList* p = &list;
	struct WordList* pnext;
	int i;
	int word_size = 0;
	/* Search for the insertion place. */
	while (p->next != NULL && p->next->value <= value)
	{
		p = p->next;
	}

	/* Insert a new cell. */
	pnext = p->next;
	p->next = (struct WordList*)malloc(sizeof(struct WordList));
	assert(p->next != NULL);
	p->next->value = value;
	p->next->next = pnext;

	/* Copy the word */
	i = 0;
	while (buffer[i] != '\0') {
		i++;
	}
	word_size = i;
	assert(word_size > 0);
	p->next->word = (char*)malloc((word_size + 1) * sizeof(char));
	i = 0;
	while (buffer[i] != '\0') {
		p->next->word[i] = buffer[i];
		i++;
	}
	p->next->word[word_size] = '\0';
}

void DeleteWordList(struct WordList list)
{
	if (list.next != NULL && list.next->next != NULL) {
		DeleteWordList(*list.next);
	}
	if (list.next != NULL)
	{
		free(list.next->word);
		free(list.next);
	}
}

void PrintWordList(struct WordList list)
{
	struct WordList* p = list.next;
	while (p != NULL)
	{
		printf("%d: %s\n", p->value, p->word);
		p = p->next;
	}
}

void PrintWordsSorted(const char* str)
{
	char* buffer = (char*)malloc(256 * sizeof(char));
	struct WordList words;
	size_t i = 0;
	char c;
	char* value;
	assert(buffer != NULL);
	buffer[255] = '\0';
	CreateWordList(words);

	/* iterate on each word. */
	do {
		c = *str;
		buffer[i] = c;
		if ((c == ' ' || c == '\0') && i > 0) {
			// Add this word to the list.
			value = SumCharsAndDigits(buffer);
			InsertWordList(words, buffer, value[0] - '0');
			i = 0;
		}
		i++;
		str++;
	} while (c != '\0');

	PrintWordList(words);

	DeleteWordList(words);
	free(buffer);
}

void SumCharsAndDigitsTest(const char* str, const char* oracle)
{
	char* result = SumCharsAndDigits(str);
	const char* pResult = result;
	const char* pOracle = oracle;

	printf("Testing SumCharsAndDigits(%s)...\t", str);

	/* Compare the result with the oracle. */
	while (*pResult != '\0' && *pOracle != '\0') {
		if (*pResult != *pOracle) {
			printf("failed.\n");
			printf("\tSumCharsAndDigits(%s) returned %s instead of %s.\n", str, result, oracle);
			free(result);
			assert(false);
		}
		pResult++;
		pOracle++;
	}

	printf("passed (result = %s).\n", result);

	free(result);
}

int SumDigits(int number)
{
	int quot = number;
	int sum = 0;

	/* Add each digit to the sum */
	while (quot > 0) {
		sum += quot % 10;
		quot /= 10;
	}

	return sum;
}

