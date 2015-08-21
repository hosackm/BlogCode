import pytest
import stack


@pytest.fixture
def stack():
    return stack.Stack()


def test_stack_starts_empty(stack):
    assert(stack.empty() is True)


def test_stack_push_not_empty(stack):
    stack.push(0)
    assert(stack.empty() is False)


def test_push_one_pop_one_equals(stack):
    stack.push(0)
    assert(stack.pop() == 0)


def test_push_multiple_pop_multiple_equals(stack):
    for i in xrange(100):
        stack.push(i)

    for i in xrange(100):
        assert(stack.pop() == 99 - i)


def test_str_empty_stack(stack):
    assert(str(stack) == 'List()')


def test_str_nonempty_stack(stack):
    stack.push(0)
    stack.push(1)
    assert(str(stack) == 'List(0, 1)')
