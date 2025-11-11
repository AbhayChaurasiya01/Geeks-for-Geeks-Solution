class Solution:
    #Function to find a continuous sub-array which adds up to a given number.
    def subarraySum(self, arr, target):
        # Your code here
        n = len(arr)
        curr_sum = 0
        left = 0
        
        for right in range(n):
            curr_sum += arr[right]
            
            # Shrink window if sum exceeds target
            while curr_sum > target and left < right:
                curr_sum -= arr[left]
                left += 1
            
            # If target found, return 1-based indices
            if curr_sum == target:
                return [left + 1, right + 1]
        
        # If no subarray found
        return [-1]
