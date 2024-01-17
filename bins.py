import numpy as np

#n_bins = 100
#bin_edges = np.logspace(0.1, 2, n_bins)

# Offset the array to start from 0
#bin_edges -= bin_edges[0]

# Round bin edges to 5 decimal places
#bin_edges = np.round(bin_edges, 5)

# Print the generated bin edges
#print(f"n_bins = {n_bins}")
#print(f"bin_edges = {list(bin_edges)}")


import numpy as np

adjusted_interval_list = np.round(np.arange(0, 100.1, 0.1), 1).tolist()

print(f"bin_edges = {list(adjusted_interval_list)}")
