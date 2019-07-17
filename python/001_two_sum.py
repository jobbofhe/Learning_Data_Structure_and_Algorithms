
"""
class Solution(object):
    def twosum(self, nums, target):
        for i in range(len(nums)):
            for j in range(i+1, len(nums)):
                if nums[i] + nums[j] == target:
                    return [i, j]

array = [1, 2, 3, 4, 5]
target = 6
obj = Solution()
re = obj.twosum(array, target)

print(re)

"""


class Solution(object):
    def twosum(self, nums, target):
        lookup = {}
        for i, num in enumerate(nums):
            if target - num in lookup:
                return [lookup[target-num], i]
            else:
                lookup[num] = i
                print(lookup)
                print("")

array = [1, 2, 3, 4, 5]
target = 8
obj = Solution()
re = obj.twosum(array, target)

print(re)            
