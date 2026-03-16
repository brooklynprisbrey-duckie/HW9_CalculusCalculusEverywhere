#include <iostream>
#include <cmath>
#include <sstream> //delete after testing
using namespace std;

const int arraySize = 20;

struct StoreValues {
    int numCount=0;
    double mean=0;
    double median=0;
    double modeArray[2][arraySize];
    double range=0;
    double svariance=0;
    double standdist=0;
    void printArr(double* arrpointer);
    double aAverage(double* arrpointer);
    double aMedian(double* arrpointer);
    double aMode(double* arrpointer);
    double aVariance(double* arrpointer);
};

int pullArr(double* arrpointer, int placeholder);

void sort(double* arrpointer, int numcount);

int main(){
    cout << "hello world\n"
        "it is calculus time\n" << endl;

    StoreValues UserValues;
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
    UserValues.numCount = numCount;

    double sortArray[arraySize];
    copy(inputArray, inputArray + numCount, sortArray);
    sort(sortArray, numCount);

    UserValues.printArr(sortArray);

    UserValues.aAverage(sortArray);
    cout << "Central Tendency\n"
        "Average of dataset: " << UserValues.mean << endl;

    UserValues.aMedian(sortArray);
    cout << "Median of dataset: " << UserValues.median << endl;

    UserValues.aMode(sortArray);


    UserValues.range = sortArray[numCount - 1] - sortArray[0];
    cout << "Dispersion\n"
        "Range of dataset: " << UserValues.range << endl;

    UserValues.aVariance(sortArray);
    cout << "Sample variance of dataset: " << UserValues.svariance << endl;

    UserValues.standdist = pow(UserValues.svariance,0.5);
    cout << "Standard distribution of dataset: " << UserValues.standdist << endl;



    return 0;
}

//pass in pointer to array, leaves on failure in insert.
int pullArr(double* arrpointer, int placeholder) {
    istringstream testing{};//replace testing with cin
    testing.str("85 90 83 92 100");

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

void StoreValues::printArr(double* arrpointer) {
    for (int i = 0; i < numCount; i++) {
        cout << '[' << arrpointer[i] << ']';
    }
    cout << endl;
    return;
}

double StoreValues::aAverage(double* arrpointer) {
    double total = 0;
    for (int i = 0; i < numCount; i++) {
        total += arrpointer[i];
    }
    mean = total / numCount;
    return total / numCount;
};

double StoreValues::aMedian(double* arrpointer) {
    int iMedian = (numCount / 2);
    median = arrpointer[iMedian];
    if (!(numCount % 2)) {
        median += arrpointer[iMedian - 1];
        median /= 2;
    }
    return median;
};

double StoreValues::aMode(double* arrpointer) {
    int placeholder = 0;
    for (int j = 0; j < numCount; j++)
        for (int i = 0; i < numCount; i++) {
            if (arrpointer[i] == modeArray[0][placeholder]) {
                modeArray[1][placeholder] += 1;
            }
            else {
                modeArray[0][placeholder] = arrpointer[i];
                modeArray[1][placeholder] = 0;
                placeholder += 1;
            }
        }
    return modeArray[0][placeholder];
};

double StoreValues::aVariance(double* arrpointer) {
    for (int i = 0; i < numCount; i++) {
        double ph = arrpointer[i] - mean;
        svariance += pow(ph, 2);
    }
    svariance /= (numCount - 1);
    return svariance;
}

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