package main

import "fmt"

type Node struct {
    left *Node
    right *Node
    elem interface{}
}
type Tree struct {
    root *Node
    size int
}

func (n *Node) cmp(other *Node) bool {
    return n.elem.(int) > other.elem.(int)
}

func (t *Tree) Insert(e interface{}) {
    if t.root == nil {
        t.root = &Node{nil, nil, e}
    } else {
        t.root.insert(e)
    }
    t.size += 1
}

func (n *Node) insert(e interface{}) {
    if e.(int) < n.elem.(int) {
        if n.left == nil {
            n.left = &Node{nil, nil, e}
        } else {
            n.left.insert(e)
        }
    } else {
        if n.right == nil {
            n.right = &Node{nil, nil, e}
        } else {
            n.right.insert(e)
        }
    }
}

func (t *Tree) String() (s string) {
    s += "Tree("
    s += fmt.Sprintf("size:%d", t.size)
    s += ")"
    return
}

func main() {
    t := new(Tree)

    t.Insert(42)
    t.Insert(43)
    t.Insert(20)
    t.Insert(0)
    t.Insert(100)

    fmt.Println(t)
}
