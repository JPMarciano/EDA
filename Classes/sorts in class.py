# -*- coding: utf-8 -*-

def counting_sort(a, k):
    counts = [0]*k
    for i in a:
        counts[i]+=1
    result = []
    for i in range(len(counts)):
        result += [i]*counts[i]
    return result

def bucket_sort(a, k, nbuckets):
    # a consists of n (key, value)
    buckets = [[]]*nbuckets
    for t in a:
        buckets[int(t[0] / (k / nbuckets))].append(t)
    if nbuckets < k:
        for bucket in buckets:
            counting_sort(bucket[:][0], k)
    result = [buckets[i] for i in range(k)]
    return result


print(counting_sort([2,4,4,5,6,2,2,0,1,1], 7))

print(bucket_sort([(2,0),(4,0),(4,0),(5,0),(6,0),(2,0),(2,0),(0,0),(1,0),(1,0)], 9, 3))