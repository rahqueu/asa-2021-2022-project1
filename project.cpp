#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define MAXSIZE 5000

typedef vector<vector<int>> hashTable;

hashTable table = hashTable(MAXSIZE);
int decreasingOrEqual = 0;

int readInteger(int* number) {

    int c, answer = 0;
    bool negative = false, space = false, input = false;

    while ((c = getchar()) != '\n' && c != ' ') {
        input = true;
        if (c == '-') negative = true;
        else {
            if (negative) answer = answer * 10 - c + '0';
            else answer = answer * 10 + c - '0';
        }
    }

    *number = answer;
    
    c == ' ' ? space = 1 : space = 0;

    if (input) return space;
    else return -1;
}

vector<int> parse1(void) {

    int* number = (int*) malloc(sizeof(int)), inputWasGiven = 0;
    float max = INFINITY;
    vector<int> input = vector<int>();

    while ((inputWasGiven = readInteger(number)) == 1) {
        if (*number <= max) {
            // If the sequence is not increasing, we increment the variable
            decreasingOrEqual++;
            max = *number;
        }
        input.push_back(*number);
    }
    if (inputWasGiven == 0) input.push_back(*number);

    return input;
}

vector<int> biggestSubSeq(vector<int> array, int size) {

    vector<int> aux1 = vector<int>(size, 1), aux2 = vector<int>(size, 1), answer = vector<int>(2, 0);

    // If the input array is always decreasing
    if (decreasingOrEqual == size - 1) return {1, size};
    // If the input array is either always the same number, or strictly decreasing
    else if (decreasingOrEqual == size && size != 0) return {size, 1};

    // If input array has no numbers, there aren't any subsequences.
    if (size == 0) return {0, 0};
    else answer[0] = 1;

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (array[i] > array[j]) {
                // If condition verifies, our current number can be added to the 
                // current subsequence in order to increase its size
                if (aux1[j] + 1 > aux1[i]) {
                    aux1[i] = aux1[j] + 1;
                    aux2[i] = aux2[j];
                }
                // If condition verifies, then we have another subsequence with the same size.
                else if (aux1[j] + 1 == aux1[i]) {
                    aux2[i] = aux2[i] + aux2[j];
                }
            }
            // If the current subsequence is bigger than the previous one, update it. 
            if (aux1[i] > answer[0]) {
                answer[0] = aux1[i];
                answer[1] = 0;
            }
        }
        // If is the same size, increment the counter.
        if (aux1[i] == answer[0]) answer[1] += aux2[i];
    }

    return answer;
}

void problem1(void) {

    vector<int> input = parse1();
    int size = input.size();
    vector<int> answer = biggestSubSeq(input, size);

    cout << answer[0] << " " << answer[1] << endl;
}

int hashFunction(int number) {

    return number % MAXSIZE;
}

bool hashContains(int number) {
    int index = hashFunction(number), size = table[index].size();

    for (int i = 0; i < size; i++) {
        if (table[index][i] == number) return true;
    }

    return false;
}

vector<int> parse2_1(void) {

    int* number = (int*) malloc(sizeof(int)), inputWasGiven = 0;
    vector<int> input = vector<int>();

    while ((inputWasGiven = readInteger(number)) == 1) {
        input.push_back(*number);
        // Save the number in the hash function
        table[hashFunction(*number)].push_back(*number);
    }
    if (inputWasGiven == 0) {
        input.push_back(*number);
        table[hashFunction(*number)].push_back(*number);
    }

    return input;
}

vector<int> parse2_2(void) {

    int* number = (int*) malloc(sizeof(int)), inputWasGiven = 0;
    vector<int> input = vector<int>();

    while ((inputWasGiven = readInteger(number)) == 1) {
        // If the number exists in the first array, save it
        if (hashContains(*number)) input.push_back(*number);
    }
    if (inputWasGiven == 0) if (hashContains(*number)) input.push_back(*number);

    return input;
}

int biggestCommonSubSeq(vector<int> array1, vector<int> array2) {

    int size1 = array1.size(), size2 = array2.size(), max = 0;
    vector<int> answers = vector<int>(size2, 0);

    for (int i = 1; i < size1 + 1; i++) {
        // The size of the sequence starts at 0.
        int size = 0;
        for (int j = 1; j < size2 + 1; j++) {
            // If condition verifies, we are evaluating the same number and we can increase the size of the sequence.
            if (array1[i-1] == array2[j-1] && size + 1 > answers[j-1]) {
                answers[j-1] = size + 1;
                // We find the biggest length of common subsequences stored in the answers array.
                if (answers[j-1] > max) max = answers[j-1];
            }
            // If condition verifies there is a previous smaller number in the common subsequence.
            if (array1[i-1] > array2[j-1] && answers[j-1] > size)
                size = answers[j-1];
        }
    }

    return max;
}

void problem2(void) {

    vector<int> input1 = parse2_1(), input2 = parse2_2();

    cout << biggestCommonSubSeq(input1, input2) << endl;
}

int main(void) {

    int problem;

    cin >> problem;
    getchar();

    switch (problem)
    {
    case 1:
        problem1();
        break;
    case 2:
        problem2();
        break;
    default:
        cout << "Problema inexistente\n";
        break;
    }

    return 0;
}