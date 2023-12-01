import numpy as np

n_bins = 100
bin_edges = np.logspace(0, 2, n_bins)

# Offset the array to start from 0
bin_edges -= bin_edges[0]

# Print the generated bin edges
print(f"n_bins = {n_bins}")
print(f"bin_edges = {list(bin_edges)}")