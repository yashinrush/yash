#include <iostream>
#include <vector>
#include <queue>  // For heap operations

using namespace std;

void findMaxMinMarks(vector<int>& marks) {
    // Max-Heap (to find the maximum mark)
    priority_queue<int> maxHeap;
    // Min-Heap (to find the minimum mark)
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Insert all marks into both heaps
    for (int mark : marks) {
        maxHeap.push(mark); // Max-Heap
        minHeap.push(mark); // Min-Heap
    }
    
    // Extract maximum from max-heap
    int maxMark = maxHeap.top();
    
    // Extract minimum from min-heap
    int minMark = minHeap.top();
    
    // Output the results
    cout << "Maximum Marks: " << maxMark << endl;
    cout << "Minimum Marks: " << minMark << endl;
}

int main() {
    int n;
    
    // Input number of students
    cout << "Enter the number of students: ";
    cin >> n;
    
    vector<int> marks(n);
    
    // Input marks of students
    cout << "Enter the marks of the students: ";
    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }
    
    // Find and display the maximum and minimum marks
    findMaxMinMarks(marks);
    
    return 0;
}
