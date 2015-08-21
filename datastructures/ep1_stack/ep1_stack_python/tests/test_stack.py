import pytest
import sys
sys.path.append('.')
import stack
sys.path.remove('.')


@pytest.fixture
def stackfixture():
    return stack.Stack()


def test_stack_starts_empty(stackfixture):
    assert(stackfixture.empty() is True)


def test_stack_push_not_empty(stackfixture):
    stackfixture.push(0)
    assert(stackfixture.empty() is False)


def test_push_one_pop_one_equals(stackfixture):
    stackfixture.push(0)
    assert(stackfixture.pop() == 0)


def test_push_multiple_pop_multiple_equals(stackfixture):
    for i in xrange(100):
        stackfixture.push(i)

    for i in xrange(100):
        assert(stackfixture.pop() == 99 - i)


def test_str_empty_stack(stackfixture):
    assert(str(stackfixture) == 'Stack()')


def test_str_nonempty_stack(stackfixture):
    stackfixture.push(0)
    stackfixture.push(1)
    assert(str(stackfixture) == 'Stack(0, 1)')
