package main

import (
	"fmt"
	"os"
	"strconv"
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
func calc(operator int, values []int) int {
	result := 0
	switch operator {
	case 1:
		for i := 0; i < len(values); i++ {
			result = result + values[i]
			if i == len(values)-1 {
				fmt.Print(values[i], " = ")
			} else {
				fmt.Print(values[i], " + ")
			}
		}
		return result
	case 2:
		result = values[0] * 2
		for i := 0; i < len(values); i++ {
			result = result - values[i]
			if i == len(values)-1 {
				fmt.Print(values[i], " = ")
			} else {
				fmt.Print(values[i], " - ")
			}
		}
		return result
	case 3:
		result = 1
		for i := 0; i < len(values); i++ {
			result = result * values[i]
			if i == len(values)-1 {
				fmt.Print(values[i], " = ")
			} else {
				fmt.Print(values[i], " * ")
			}
		}
		return result
	default:
		return 0
	}
}

func UNUSED(x ...interface{}) {}

func main() {
	var vals = make([]int, len(os.Args)-2)
	for i := 2; i < len(os.Args); i++ {
		num, err := strconv.ParseInt(os.Args[i], 10, 0)
		vals[i-2] = int(num)
		UNUSED(err)
	}

	if os.Args[1] == "add" {
		fmt.Println(calc(1, vals))

	} else if os.Args[1] == "sub" {
		fmt.Println(calc(2, vals))

	} else if os.Args[1] == "mult" {
		fmt.Println(calc(3, vals))

	} else {
		fmt.Println("Invalid input")
	}

}
