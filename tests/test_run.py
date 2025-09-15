import fastlib
import pytest

class MyShift(fastlib.Transformer):
    def __init__(self, shift):
        super().__init__()
        self.shift = shift

    def name(self):
        return "MyShift"

    def apply(self, m):
        out = fastlib.Matrix(m.rows(), m.cols(), 0.0)
        for i in range(m.rows()):
            for j in range(m.cols()):
                out.set(i, j, m.get(i, j) + self.shift)
        return out

def test_matrix_init_and_get_set():
    m = fastlib.Matrix(2, 2, 3.0)
    assert m.rows() == 2
    assert m.cols() == 2
    for i in range(2):
        for j in range(2):
            assert m.get(i, j) == 3.0
            m.set(i, j, 5.0)
            assert m.get(i, j) == 5.0

def test_scale_transformer():
    m = fastlib.Matrix(2, 2, 2.0)
    scale = fastlib.ScaleTransformer(3.0)
    result = scale.apply(m)
    for i in range(result.rows()):
        for j in range(result.cols()):
            assert result.get(i, j) == 6.0
    assert scale.name() == "Scale"

def test_myshift_transformer():
    m = fastlib.Matrix(2, 2, 1.0)
    shift = MyShift(4.0)
    result = shift.apply(m)
    for i in range(result.rows()):
        for j in range(result.cols()):
            assert result.get(i, j) == 5.0
    assert shift.name() == "MyShift"

def test_repr():
    m = fastlib.Matrix(2, 2, 1.0)
    r = m.repr()
    assert isinstance(r, str)
    assert "Matrix" in r

def test_row_norms():
    m = fastlib.Matrix(3, 3, 0.0)
    m.set(0, 0, 3.0)
    m.set(0, 1, 4.0)
    m.set(1, 1, 5.0)
    m.set(2, 2, 12.0)
    norms = fastlib.row_norms(m)
    assert len(norms) == 3
    assert norms[0] == 5.0  # sqrt(3^2 + 4^2)
    assert norms[1] == 5.0  # sqrt(5^2)
    assert norms[2] == 12.0 # sqrt(12^2)

def test_identity():
    I = fastlib.identity(4)
    assert I.rows() == 4
    assert I.cols() == 4
    for i in range(4):
        for j in range(4):
            if i == j:
                assert I.get(i, j) == 1.0
            else:
                assert I.get(i, j) == 0.0

def test_scale_transformer_on_identity():
    t = fastlib.ScaleTransformer(2.5)
    I = fastlib.identity(3)
    result = t.apply(I)
    for i in range(3):
        for j in range(3):
            if i == j:
                assert result.get(i, j) == 2.5
            else:
                assert result.get(i, j) == 0.0

def test_scale_transformer_int_on_identity():
    t_int = fastlib.ScaleTransformer(3)
    I = fastlib.identity(3)
    result = t_int.apply(I)
    for i in range(3):
        for j in range(3):
            if i == j:
                assert result.get(i, j) == 3.0
            else:
                assert result.get(i, j) == 0.0

def test_safe_divide_int():
    assert fastlib.safe_divide_int(10, 3) == 3
    assert fastlib.safe_divide_int(9, 3) == 3

def test_safe_divide_double():
    assert fastlib.safe_divide_double(10.0, 2.0) == 5.0
    assert fastlib.safe_divide_double(9.0, 3.0) == 3.0

def test_safe_divide_int_zero():
    with pytest.raises(Exception):
        fastlib.safe_divide_int(5, 0)

def test_static_matrix2d_identity_and_access():
    I2 = fastlib.StaticMatrix2d.identity()
    assert I2[0, 0] == 1.0
    assert I2[0, 1] == 0.0
    I2[0, 1] = 5.0
    assert I2[0, 1] == 5.0
    assert str(I2).startswith("StaticMatrix")