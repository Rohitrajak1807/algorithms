package main

import (
	"cmp"
	"fmt"
)

func mergeSort[O cmp.Ordered](lst []O) []O {
	if len(lst) <= 1 {
		return lst
	}
	return _mergeSort(lst, 0, len(lst)-1)
}

func _mergeSort[O cmp.Ordered](lst []O, low int, high int) []O {
	if low == high {
		return []O{lst[low]}
	}
	mid := (low + high) / 2
	left := _mergeSort(lst, low, mid)
	right := _mergeSort(lst, mid+1, high)
	return merge(left, right)
}

func merge[O cmp.Ordered](left []O, right []O) []O {
	merged := []O{}
	lenL := len(left)
	lenR := len(right)
	i, j := 0, 0

	for i != lenL && j != lenR {
		if left[i] <= right[j] {
			merged = append(merged, left[i])
			i++
		} else {
			merged = append(merged, right[j])
			j++
		}
	}
	for i < lenL {
		merged = append(merged, left[i])
		i++
	}
	for j < lenR {
		merged = append(merged, right[j])
		j++
	}
	return merged
}

func main() {
	lst := []int{9, 7, 6, 34, 23, 9, 12, 1, -1}
	fmt.Println(mergeSort(lst))
}
