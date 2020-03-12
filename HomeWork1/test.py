import numpy as np
import time


def merge(A, B):
		result = []
		while len(A) > 0 and len(B) > 0:
				if A[0] < B[0]:
					result.append(A[0])
					A.pop(0)
				else:
					result.append(B[0])
					B.pop(0)
		result += A
		result += B
		return result


def insert_sort(a):
    for i in range(len(a)):
        cv = a[i]
        j = i-1
        while j >= 0 and a[j] > cv:
            a[j+1] = a[j]
            j = j - 1
        a[j+1] = cv

def merge_sort(a):
    if len(a) <= 1:
        return a
    left = a[:int(len(a)/2)]
    right = a[int(len(a)/2):]
    return merge(merge_sort(left), merge_sort(right))


def is_sorted(a):
    for i in range(len(a)-1):
        if a[i] > a[i+1]:
            return False
    return True


def main():
    ns = np.linspace(10000, 100000, 10)
    for n in ns:

        a = [np.random.randint(0,1000000) for i in range(int(n))]
        b = a.copy()

        # call insert_sort and  calculate the time for a random array
        start = time.time()
        insert_sort(a)
        end = time.time()
        if not is_sorted(a):
            print("ERROR1")
        t1 = end-start

        # call merge_sort and  calculate the time for a random array
        start = time.time()
        sorted_a = merge_sort(b)
        end = time.time()
        if not is_sorted(sorted_a):
            print("ERROR2")
        t2 = end-start
	print("Random")
        print("(%d, %f, %f)" % (n, t1, t2))
        
        
        # call insert_sort and  calculate the time for an ascending array
        start = time.time()
        insert_sort(a)
        end = time.time()
        if not is_sorted(a):
            print("ERROR1")
        t1 = end-start
        
        # call merge_sort and  calculate the time for an ascending array
        start = time.time()
        sorted_a = merge_sort(a)
        end = time.time()
        if not is_sorted(sorted_a):
            print("ERROR2")
        t2 = end-start
        print("Ascending")
        print("(%d, %f, %f)" % (n, t1, t2))
        
        a.reverse()
        sorted_a.reverse()
        
        # call insert_sort and  calculate the time for a descending array
        start = time.time()
        insert_sort(a)
        end = time.time()
        if not is_sorted(a):
            print("ERROR1")
        t1 = end-start
        
        # call merge_sort and  calculate the time for a descending array
        start = time.time()
        sorted_a = merge_sort(sorted_a)
        end = time.time()
        if not is_sorted(sorted_a):
            print("ERROR2")
        t2 = end-start
        print("Descending")
        print("(%d, %f, %f)" % (n, t1, t2))
        

if __name__ == "__main__":
    main()
