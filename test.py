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
    return a

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

        a = [np.random.randint(0,100) for i in range(int(n))]
        b = np.copy(a)

        # call insert_sort and  calculate the time
        start = time.time()
        sorted_a = insert_sort(b)
        if not is_sorted(sorted_a):
            print("ERROR1")
        end = time.time()
        t1 = end-start

        # call merge_sort and  calculate the time
        start = time.time()
        sorted_a = merge_sort(a)
        if not is_sorted(sorted_a):
            print("ERROR2")
        end = time.time()
        t2 = end-start

        print("%d %f %f" % (n, t1, t2))


if __name__ == "__main__":
    main()
