#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

const int arraySize = 15;

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
    string aMode(double* arrpointer);
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

    cout << "Modes of dataset: " << UserValues.aMode(sortArray) << endl;

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

    cout << "Enter list of numbers, space-seperated. Enter 'done' when done." << endl;
    for (placeholder; placeholder < arraySize; placeholder++) {

        cin >> arrpointer[placeholder];

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

string StoreValues::aMode(double* arrpointer) {
    int placeholder = 0;
    for (int j = 0; j < numCount; j++) {
        bool update = true;
        for (int i = 0; i < numCount; i++) {
            if (arrpointer[j] == modeArray[0][i]) {
                modeArray[1][i] += 1;
                update = false;
            }
        }
        if (update) {
            modeArray[0][placeholder] = arrpointer[j];
            modeArray[1][placeholder] = 0;
            placeholder += 1;
        }
    }
    int max = 0;
    int min = numCount;
    for (int i = 0; i < placeholder; i++) {
        if (modeArray[1][i] > max) {
            max = modeArray[1][i];
        }
        else if (modeArray[1][i] < min) {
            min = modeArray[1][i];
        }
    }
    if (max != min) {
        string maxList = "";
        for (int i = 0; i < placeholder; i++) {
            if (modeArray[1][i] == max) {
                ostringstream strs;
                strs << modeArray[0][i];
                maxList += strs.str();
                maxList += ", ";
            }
        }
        return maxList;
    }
    else return "No mode";
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