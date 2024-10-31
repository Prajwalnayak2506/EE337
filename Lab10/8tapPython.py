import numpy as np
from scipy.signal import firwin, freqz
import matplotlib.pyplot as plt

# Define parameters
sampling_freq = 200000  # Hz
cutoff_freq = 2000  # Hz
num_taps = 8

# Calculate normalized cutoff frequency
nyquist_freq = 0.5 * sampling_freq
normalized_cutoff_freq = cutoff_freq / nyquist_freq

# Design the filter using firwin
filter_coeffs = firwin(num_taps, normalized_cutoff_freq)

# Frequency response
w, h = freqz(filter_coeffs, worN=8000)
freq = w * sampling_freq / (2 * np.pi)

# # Plot frequency response
# plt.figure()
# plt.plot(freq, np.abs(h))
# plt.title("Low Pass Filter Frequency Response")
# plt.xlabel("Frequency (Hz)")
# plt.ylabel("Magnitude")
# plt.grid()
# plt.show()

print((filter_coeffs))