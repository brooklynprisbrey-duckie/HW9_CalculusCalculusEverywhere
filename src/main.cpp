#include <iostream>
#include <sstream> //delete after testing
using namespace std;

int pullArr(double* arrpointer, int placeholder);

void sort(double* arrpointer);

const int arraySize = 10; //for easy adjustment

int main(){


    cout << "hello world\n"
        "it is calculus time\n" << endl;

    double inputArray[arraySize][arraySize];//array of array is for results. keep input array simple
    int numCount = 0;

    for (int j = 0; j < arraySize; j++) {
        for (int i = 0; i < arraySize; i++) {
            i = pullArr(inputArray[j], i);//adjust position in array
            numCount += i;
            cout << numCount << " numbers entered\n"
                "Is that all? Enter 'y' if it is." << endl;
            if (cin.peek() == 'y' || cin.peek() == 'Y') {
                break;
            }
        }
        if (cin.peek() == 'y' || cin.peek() == 'Y') {//passes out break
            break;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    double sortArray = inputArray;
    sort(sortArray[1]);

    return 0;
}

//pass in pointer to array, leaves on failure in insert.
int pullArr(double* arrpointer, int placeholder) {
    istringstream testing{};//replace testing with cin
    testing.str("0.11 0.2234 762.256 51.860\n 666.777 10.01\n 8 8 8 8 8");

    cout << "Enter list of numbers, space-seperated." << endl;
    for (placeholder; placeholder < arraySize; placeholder++) {

        testing >> arrpointer[placeholder];

        if (testing.fail()) {
            testing.clear();
            testing.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return placeholder;
};

void sort(double* arrpointer) {
    for (int j = 0; j < arraySize; j++) {
        int minIndex = j;
        for (int i = j; i < arraySize; i++) {
            if (arrpointer[i] < arrpointer[minIndex]) minIndex = i;
        }
        double temp = arrpointer[j];
        arrpointer[j] = arrpointer[minIndex];
        arrpointer[minIndex] = temp;
    }
};