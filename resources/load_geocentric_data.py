from pathlib import Path
from struct import unpack
import numpy as np

gc_data_file = Path.cwd() / "geocentric.data"

with open(gc_data_file, "rb") as f:
    gc_data_bytes = f.read()

offset, delta, count = unpack("<qqq", gc_data_bytes[:24])

gc_data = np.array(
    [unpack("<ddd", gc_data_bytes[(24+24*l):(48+24*l)]) for l in range(count)]
)

gc_data_txt = Path.cwd() / "geocentric_data.txt"
with open(gc_data_txt, "r") as f:
    first_line = map(int, f.readline().split(","))
    assert offset == next(first_line)
    assert delta == next(first_line)
    assert count == next(first_line)
    f.readline()
    cpp_gc_data = map(
        lambda line: list(map(float, line.strip().split(","))),
        f.readlines())

cpp_gc_data = np.array(list(cpp_gc_data))

assert np.allclose(gc_data, cpp_gc_data)