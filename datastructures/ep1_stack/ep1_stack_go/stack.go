package main

import "fmt"
import "errors"

type Element int
type Stack struct {
    Values []Element
}

func (s *Stack) Len() int {
    return len(s.Values)
}

func (s *Stack) Push(e Element) {
    s.Values = append(s.Values, e)
}

func (s *Stack) Pop() (Element, error) {
    if len(s.Values) < 1 {
        return -1, errors.New("Can not Pop from empty Stack")
    }

    x, v := s.Values[0], s.Values[1:]
    s.Values = v

    return x, nil
}

/* Helper printing function */
func (s *Stack) String() string {
    r := "Stack["    
    for i, v := range s.Values {
        if i > 0 {
            r += ", "
        }
        r += fmt.Sprintf("%v", v)
    }
    return r + "]"
}

func main() {
    s := new(Stack)

    fmt.Println(s)

    s.Push(1)
    s.Push(2)
    s.Push(3)
    s.Push(4)

    fmt.Println(s)

    for i := 0; i < 5; i++ {
        if v, err := s.Pop(); err != nil {
            fmt.Println(err)
        } else {
            fmt.Println("Popped:", v)
        }
    }
}
