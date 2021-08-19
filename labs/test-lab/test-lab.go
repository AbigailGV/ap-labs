package main

import (
	"fmt"
	"os"
)

func main() {
	//os.Args[0] is the program name
	if len(os.Args) > 1{ //if there are arguments
		name := os.Args[1]
		fmt.Printf("%v, welcome to the jungle!\n", name )
		
	}else{ //if they are missing
		fmt.Printf("You need to put a name!\n")
	}
}
