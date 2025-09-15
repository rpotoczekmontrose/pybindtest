import fastlib


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


M = fastlib.Matrix(3, 3, 1.0)
scale = fastlib.ScaleTransformer(2.0)
print(scale.name(), scale.apply(M).repr())

shift = MyShift(5.0)
print(shift.name(), shift.apply(M).repr())

# Build a matrix
M = fastlib.Matrix(3, 3, 0.0)
M.set(0, 0, 3.0)
M.set(0, 1, 4.0)
M.set(1, 1, 5.0)
M.set(2, 2, 12.0)

print("Matrix:\n", M.repr())

# Call parallelized C++ function
norms = fastlib.row_norms(M)
print("Row norms (parallel computed):", norms)

# Identity via C++ helper
I = fastlib.identity(4)
print("Identity:\n", I.repr())

# Create a transformer for doubles
t = fastlib.ScaleTransformer(2.5)
print(t.name())   # "ScaleTransformer"
print(t.apply(fastlib.identity(3)).repr())  # scales the identity matrix

# Create a transformer for ints
t_int = fastlib.ScaleTransformer(3)
print(t_int.name())   # "ScaleTransformer"
print(t_int.apply(fastlib.identity(3)).repr())

print("safe_divide_int(10, 3) =", fastlib.safe_divide_int(10, 3))
print("safe_divide_double(10.0, 3.0) =", fastlib.safe_divide_double(10.0, 3.0))
print("safe_divide_double(10.0, 0.0) =", fastlib.safe_divide_double(10.0, 0.0))

try:
    fastlib.safe_divide_int(5, 0)
except Exception as e:
    print("Caught error:", e)

I2 = fastlib.StaticMatrix2d.identity()
print(I2)  # StaticMatrix(2x2)

# Access elements
print(I2[0, 0])   # 1.0
print(I2[0, 1])   # 0.0

# Modify element
I2[0, 1] = 5.0
print(I2[0, 1])   # 5.0
