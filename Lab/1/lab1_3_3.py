print("*** Fun with permute ***")
str = input("input : ")
l = str.split(",")
print("Original Cofllection:  [", end = "")
a = []
for i in range(len(l)):
    print(l[i],end = "")
    if i < (len(l) - 1):
        print(", ",end = "")
    else:
        print("]")
    a.append(int(l[i]))



def permute(nums):
  result_perms = [[]]
  for n in nums:
    new_perms = []
    for perm in result_perms:
      for i in range(len(perm)+1):
        new_perms.append(perm[:i] + [n] + perm[i:])
        result_perms = new_perms
  return result_perms

my_nums = a

print("Collection of distinct numbers:\n",permute(my_nums))

