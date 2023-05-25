#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

// EX1: buyCar(int *nums, int length, int k) --> số tiền k có thể mua tối đa bao
// nhiêu sản phẩm thuộc mảng nums ??
/**
 * 1. Tạo 1 hàm sắp xếp mảng theo thứ tự tăng dần (bubble Sort)
 * 2. Impletation buyCar
*/
void bubleSort(int arr[], int n){
    for (int i = 0; i < n-1;i++){
        for (int j = n - 1; j > i;j--){
            if(arr[j] < arr[j-1]){
                swap(arr[j], arr[j - 1]);
            }
        }
    }
}
int buyCar(int *nums, int length, int k){
    int total = 0;
    bubleSort(nums, length);
    for (int i = 0; i < length;i++){
        if(k >= *(nums + i)){
            k -= *(nums + i);
            total++;
        }
    }
    return total;
}

// EX2: bool consecutiveOnes(vector<int>& nums) --> //! ktra các số 1 có LIỀN KỀ nhau
bool consecutiveOnes(vector<int>& nums){
    // !2TH: 
    /**
     * 1. nếu vector 0 phần tử -> true
     * 2. nếu i = 1 --> xét [i và i-1  và i+1] 
    */
    if(nums.size() == 0){
        return true;
    }
    for (int i = 0; i < nums.size();i++){
        if(nums[i] == 1 && (nums[i] != nums[i-1] && nums[i] != nums[i+1]))
            return false;
    }
    return true;
}

// EX3: [int equalSumIndex(vector<int>& nums)] --> //!trả về INDEX sao cho tổng Left của INDEX = TỔNG RIGHT INDEX
// The function returns the smallest index i such that the sum of the numbers to the left of i is equal to the sum of the numbers to the right. If no such index exists, return -1
/**
 * TH1: 0 phần tử -> return -1
 * TH2: 1 phần tử --> return index 0
 * TH3: duyệt nums
*/

int sumofChild(vector<int>&nums, int start, int end){
    int sum=0;
    for (int i = start; i < end;i++){
        sum += nums[i];
    }
    return sum;
}
int equalSumIndex(vector<int>& nums){
    if(nums.size() == 0)
        return -1;
    if(nums.size() == 1)
        return 0;
    for (int i = 0; i < nums.size();i++){
        if(sumofChild(nums,0,i) == sumofChild(nums,i+1,nums.size())){
            return i;
        }
    }
    return -1;
}

// EX4: int longestSublist(vector<string>& words); --> //! Trả về kích thước của mảng con DÀI NHẤT có arr[i] trùng chữ cái đầu tiên
/**
 * 1. khởi tạo count = 1 / currChar = word[i][0];
 * 2.
 */
int longestSublist(vector<string>& words){
    int subMax = 0;
    char currChar;
    for (int i = 0; i < words.size();i++){
        int count = 1; //! đếm tại item bắt đầu ktra --> khởi tạo == 1
        currChar = words[i][0];
        for (int j = i + 1; j < words.size();j++){
            if(currChar == words[j][0]){
                count++;
            }
        }
        if(count > subMax)
            subMax = count;
    }
    return subMax;
}

// EX5: int maxSum(int* nums, int n, int k)  //!-> chia mảng thành [K mảng con] sao cho:
/**
 *TODO:  Let S-value of each sub-array is the product of the largest element in this sub-array and the size of this sub-array. A way W, following these above rules, divides this array N into sub-arrays. S(W) is the sum of all S-values from all sub-arrays created by the way W. The way having the largest value S(W) is called Wmax.
*/
int maxSum(int* nums, int n, int k) {
    int sum = 0;
    int maxSum = 0;

    for (int i = 0; i < n; i++) {
        sum += nums[i];

        if(i >= k){
            sum -= nums[i - k];
        }
        if(i >= k-1 && sum > maxSum){
            maxSum = sum;
        }
    }

    return maxSum * k;
}

// EX6: int minimumAmplitude(vector<int>& nums, int k); 
// ! The function returns the minimum value of max(nums) - min(nums) after removing a sublist with length k from array nums.
int findMaxOrMin(vector<int> &nums, bool findMax){
    int res = findMax ? INT_MIN : INT_MAX; // res bằng MIN khi findMax là TRUE và ngược lại
    for(int x : nums){
        if(findMax){ //--> TÌM MAX
            if(res < x){
                res = x;
            }
        }else{ // TÌM MIN
            if(res > x)
                res = x;
        }
    }
    return res;
}

int minimumAmplitude(vector<int>& nums, int k){
    int res = INT_MAX;
    int size = nums.size();
    for (int i = 0; i < size - k;i++){
        vector<int> newNums = nums;
        newNums.erase(newNums.begin() + i, newNums.begin() + i + k);
        int maxVal = findMaxOrMin(newNums, true);
        int minVal = findMaxOrMin(newNums, false);
        int subVal = maxVal - minVal;
        if(res > subVal)
            res = subVal;
    }
    return res;
}

// EX7:  int steadySpeed(vector<int>& p) --> //! Trả về list có LENGTH dài nhất mà khoảng cách giữa 2 ele liên tiếp là ko đổi

// EX8: int sumLessThanTarget(vector<int>& nums, int target) --> trả về TỔNG CẶP SỐ NẰM 2 ĐẦU VECTOR LỚN NHẤT MÀ <= TARGET
int sumLessThanTarget(vector<int>& nums, int target){
    int maxsum;
    int sum;
    int left = 0;
    int right = nums.size() - 1;
    while(left < right){
        sum = nums[left] + nums[right];
        if(sum < target){
            maxsum = max(maxsum, sum);
            left++;
        }else{
            right--;
        }
    }
    return maxsum;
}

// EX9: vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations);
//!--> trả về một vector mới đã được update cộng thêm 1 lượng A  thuộc  operation: (L R A)
/**
 * 1. Khởi tạo 1 vector mới có kích thước là size - all element = 0
 * 2. tạo 1 vòng for duyệt qua toàn bộ vector operation tại mỗi element, ta tìm:
 *      + L / R / X = ???
 *      + tạo vòng for chạy từ L đến R rồi cộng result[i] + X
 * 3. duyệt qua mảng nums và cộng từng phần tử thuộc nums vào result
*/
vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations){
    vector<int> result(nums.size(), 0);
    for (int i = 0; i < operations.size();i++){
        int L = operations[i][0];
        int R = operations[i][1];
        int add = operations[i][2];
        for (int j = L; j <= R;j++){
            result[j] += add;
        }
    }
    for (int i = 0; i < nums.size();i++){
        result[i] += nums[i];
    }
    return result;
}

int main(){
	
}
