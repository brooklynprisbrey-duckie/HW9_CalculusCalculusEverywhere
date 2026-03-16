#include <iostream>
#include <sstream> //delete after testing
using namespace std;

int pullArr(double* arrpointer, int placeholder);

void printArr(double* arrpointer, int numcount);

double aAverage(double* arrpointer, int numcount);

double aMedian(double* arrpointer, int numcount);

void sort(double* arrpointer, int numcount);

const int arraySize = 20; //for easy adjustment

int main(){
    cout << "hello world\n"
        "it is calculus time\n" << endl;

    double inputArray[arraySize];//array of array is for results. keep input array simple
    int numCount = 0;

    for (int i = 0; i < arraySize; i++) {
        i = pullArr(inputArray, i);//adjust position in array
        numCount = i + 1;
        if (numCount < arraySize) {
            cout << numCount << " numbers entered\n"
                "Is that all? Enter 'y' if it is." << endl;

            cin.clear();//should be able to remove this later
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (cin.peek() == 'y' || cin.peek() == 'Y') {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
        else { 
            numCount = arraySize;
            cout << numCount << " numbers entered, array is full." << endl;
        }
    }

    double sortArray[arraySize];
    copy(inputArray, inputArray + numCount, sortArray);
    sort(sortArray, numCount);

    printArr(sortArray, numCount);

    double average = aAverage(sortArray, numCount);
    cout << "Average of dataset: " << average << endl;

    double median = aMedian(sortArray, numCount);
    cout << "Median of dataset: " << median << endl;

    return 0;
}

//pass in pointer to array, leaves on failure in insert.
int pullArr(double* arrpointer, int placeholder) {
    istringstream testing{};//replace testing with cin
    testing.str("0.11 0.2234 762.256 51.860 80.8");

    cout << "Enter list of numbers, space-seperated." << endl;
    for (placeholder; placeholder < arraySize; placeholder++) {

        testing >> arrpointer[placeholder];

        if (testing.fail()) {
            testing.clear();
            testing.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            placeholder -= 1;
            break;
        }

    }
    return placeholder;
};

void printArr(double* arrpointer, int numcount) {
    for (int i = 0; i < numcount; i++) {
        cout << '[' << arrpointer[i] << ']';
    }
    cout << endl;
    return;
}

double aAverage(double* arrpointer, int numcount) {
    double total = 0;
    for (int i = 0; i < numcount; i++) {
        total += arrpointer[i];
    }
    return total / numcount;
};

double aMedian(double* arrpointer, int numcount) {
    int iMedian = (numcount / 2);
    double median = arrpointer[iMedian];
    if (!(numcount % 2)) {
        median += arrpointer[iMedian - 1];
        median /= 2;
    }
    return median;
};

void sort(double* arrpointer, int numCount) {
    for (int j = 0; j < numCount; j++) {
        int minIndex = j;
        for (int i = j; i < numCount; i++) {
            if (arrpointer[i] < arrpointer[minIndex]) minIndex = i;
        }
        double temp = arrpointer[j];
        arrpointer[j] = arrpointer[minIndex];
        arrpointer[minIndex] = temp;
    }
};