// Visual Sorts
// Noah Eisen
// 2/19/14

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_header();
void get_array(vector<int> &arr);
void print_menu();
void quicksort(vector<int> &arr, int start, int end, int &count);
int split(vector<int> &arr, int start, int end, int &count);
void print_array(vector<int> arr);
void print_array2(vector<int> arr);
void bubblesort(vector<int> &arr);
bool compswap(int &a, int &b);
void insertionsort(vector<int> &arr);
string numberize(int i);
void mergesort(vector<int> &arr, vector<int> &temp, int low, int high);
void merge(vector<int> &arr, vector<int> &temp, int low, int pivot, int high);


int main()
{
    int counter = 0; // Yeah I am using a global. deal with it
    print_header();
    cout << "\n";
    cout << "would you like to use the default array? (y/n): ";
    char resp;
    cin >> resp;
    cout << "\n";
    int arr_in[8] = {2, 5, 4, 7, 8, 1, 3, 6};
    vector<int> arr(8);
    vector<int> default_arr(8);
    for (int i = 0; i < 8; ++i) {
	arr[i] = arr_in[i];
	default_arr[i] = arr_in[i];
    }
    // parsing input
    if (resp == 'n') {
        string junk; // bad input checking
        getline(cin, junk);
        get_array(arr);
        default_arr = arr;
    }
    else if (resp != 'y') {
        string junk; // bad input checking
        getline(cin, junk);
        cout << "That was bad input, but will just go with the default\n";
    }
    else {
        string junk; // bad input checking
        getline(cin, junk);
    }
    
    char input = 'X';
    print_menu();
    cout << "enter choice: ";
    cin >> input;
    cout << "\n";
    // main loop
    while (input != 'x') {
        arr = default_arr;
        if (input == 'n') {
            get_array(arr);
            default_arr = arr;
        }
        else if (input == 'q') {
            int count = 0;
            quicksort(arr, 0, arr.size() - 1, count);
            cout << "number of swaps: " << count << "\n\n";
        }
        else if (input == 'b')
            bubblesort(arr);
        else if (input == 'i')
            insertionsort(arr);
        else if (input != 'x')
            cout << "Invalid input\n\n";
        print_menu();
        cout << "enter choice: ";
        cin >> input;
        cout << "\n";
    }
    cout << "Goodbye!\n";
}


void print_header()
{
    cout << "/ - - - - - - - - - - - - - - - \\\n"
         << "|                               |\n"
         << "|          Visual Sorts         |\n"
         << "|                               |\n"
         << "|            -   -   -          |\n"
         << "|                               |\n"
         << "|        made by Noah Eisen     |\n"
         << "\\ - - - - - - - - - - - - - - - /\n";
}

void get_array(vector<int> &arr)
{
    while (!arr.empty())
        arr.pop_back();
    cout << "How many elements would you like in your array?: ";
    int size;
    int elt;
    cin >> size;
    cout << "\n";
    for (int i = 0; i < size; ++i) {
        cout << "enter element " << i << ": ";
        cin >> elt;
        arr.push_back(elt);
    }
    cout << "\n";
}

void print_menu()
{
    cout << "--------------------\n"
         << "input new array -- n\n"
         << "quicksort       -- q\n"
         << "bubble sort     -- b\n"
         << "insertion sort  -- i\n"
         << "quit            -- x\n"
         << "--------------------\n\n";
}

// The partitioning function
int split(vector<int> &arr, int start, int end, int &count)
{
    // pivot is end of arr
    int pivot = arr[end];
    
    cout << "Partitioning with " << pivot << " as pivot:\n";
    
    while (start < end) {
        
        cout << "  ";
        print_array(arr);
        
        // find an element that is in the left
        // part of the arr and is less than
        // pivot
        while (arr[start] < pivot) {
            start++;
        }
        
        // find an element that is in the right
        // part of the arr and is more than
        // pivot
        while (arr[end] > pivot)
            end--;
        
        // if they are the same elt
        // continue w loop
        if (arr[start] == arr[end]) {
            start++;
        }
        
        // else we swap em
        else if (start < end) {
            char tmp = arr[start];
            arr[start] = arr[end];
            arr[end] = tmp;
            ++count;
        }
    }
    
    cout << "\n";
    
    return end;
}

// The sort function (quicksort)
void quicksort(vector<int> &arr, int start, int end, int &count)
{
    
    if (start < end) {
        
        // find pivot
        int pivot = split(arr, start, end, count);
        
        // recursive calls on substrings
        quicksort(arr, start, pivot - 1, count);
        quicksort(arr, pivot + 1, end, count);
    }
}

void print_array(vector<int> arr)
{
    cout << "[ ";
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << "]\n";
}

void print_array2(vector<int> arr)
{
    cout << "[ ";
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << "]";
}

void bubblesort(vector<int> &arr)
{
    int count = 0;
    for (int i = 0; i < arr.size(); ++i) {
        cout << numberize(i + 1) << " bubble:\n";
        for (int j = arr.size() - 1; j > i; --j) {
            cout << "  ";
            if (compswap(arr[j - 1], arr[j]))
                ++count;
            print_array(arr);
        }
        cout << "\n";
    }
    cout << "number of swaps" << count << "\n\n";
}

void insertionsort(vector<int> &arr)
{
    int count = 0;
    for (int i = 1; i < arr.size(); ++i) {
        cout << numberize(i) << " insert:\n";
        int v = arr[i], j = i;
        while (v < arr[j - 1] && j >= 0) {
            arr[j] = arr[j - 1];
            j--;
            cout << "  ";
            ++count;
            print_array(arr);
        }
        arr[j] = v;
        cout << "  ";
        ++count;
        print_array(arr);
        cout << "\n";
    }
    cout << "number of moves: " << count << "\n\n";
}

bool compswap(int &a, int &b)
{
    if (a > b) {
        int tmp = a;
        a = b;
        b = tmp;
        return true;
    }
    else
        return false;
}

string numberize(int i)
{
    if (i == 1)
        return "1st";
    else if (i == 2)
        return "2nd";
    else if (i == 3)
        return "3rd";
    else {
        string str = to_string(i);
        str += "th";
        return str;
    }
}

void mergesort(vector<int> &arr, vector<int> &temp, int low, int high)
{
    int pivot;
    if(low<high) {
        pivot=(low+high)/2;
        mergesort(arr,temp,low,pivot);
        mergesort(arr,temp,pivot+1,high);
        merge(arr,temp,low,pivot,high);
    }
}

void merge(vector<int> &arr, vector<int> &temp, int low, int pivot, int high)
{
    int h, i, j, k;
    h = low;
    i = low;
    j = pivot + 1;
    
    while((h <= pivot ) && (j <= high)) {
        if(arr[h] <= arr[j]) {
            temp[i] = arr[h];
            h++;
        }
        else {
            temp[i] = arr[j];
            j++;
        }
        i++;
        cout << "arr: ";
        print_array2(arr);
        cout << "   temp: ";
        print_array(temp);
    }
    if(h > pivot) {
        for(k = j; k <= high; k++) {
            temp[i] = arr[k];
            i++;
            cout << "arr: ";
            print_array2(arr);
            cout << "   temp: ";
            print_array(temp);
        }
    }
    else {
        for(k = h; k <= pivot; k++) {
            temp[i] = arr[k];
            i++;
            cout << "arr: ";
            print_array2(arr);
            cout << "   temp: ";
            print_array(temp);
        }
    }
    for(k = low; k <= high; k++) {
        arr[k] = temp[k];
        cout << "arr: ";
        print_array2(arr);
        cout << "   temp: ";
        print_array(temp);
    }
}





