import pytest

import example

def test_vector2d_creation():
    v = example.Vector2D(3, 4)
    assert v.x == 3
    assert v.y == 4

def test_length():
    v = example.Vector2D(3, 4)
    assert v.length() == 5

def test_normalized():
    v = example.Vector2D(3, 4)
    n = v.normalized()
    assert pytest.approx(n.x) == 0.6
    assert pytest.approx(n.y) == 0.8

def test_zero_normalized():
    v = example.Vector2D(0, 0)
    n = v.normalized()
    assert n.x == 0
    assert n.y == 0

def test_repr_and_str():
    v = example.Vector2D(1, 2)
    assert str(v) == "Vector2D(1, 2)"
    assert repr(v) == "Vector2D(1, 2)"

def test_add_operator():
    v1 = example.Vector2D(1, 2)
    v2 = example.Vector2D(3, 4)
    v3 = v1 + v2
    assert v3.x == 4
    assert v3.y == 6

def test_sub_operator():
    v1 = example.Vector2D(5, 7)
    v2 = example.Vector2D(2, 3)
    v3 = v1 - v2
    assert v3.x == 3
    assert v3.y == 4

def test_mul_operator():
    v = example.Vector2D(2, 3)
    v2 = v * 4
    assert v2.x == 8
    assert v2.y == 12

def test_eq_operator():
    v1 = example.Vector2D(1, 2)
    v2 = example.Vector2D(1, 2)
    v3 = example.Vector2D(2, 1)
    assert v1 == v2
    assert v1 != v3