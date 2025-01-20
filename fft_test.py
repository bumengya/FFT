import numpy as np
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import single

# 1. 创建一个时域信号
fs = 500  # 采样频率（Hz）
# t = np.arange(0, 1, 1/fs)  # 时间向量（1秒信号）

# f1, f2 = 50, 120  # 两个信号的频率
# signal = np.sin(2 * np.pi * f1 * t) + 0.5 * np.sin(2 * np.pi * f2 * t)  # 复合信号

signal= [1,0,0,0]
t = np.linspace(0, len(signal) - 1, len(signal))
# 2. FFT：时域 -> 频域
fft_result = np.fft.fft(signal)
freqs = np.fft.fftfreq(len(fft_result), 1/fs)  # 频率轴
magnitude = np.abs(fft_result)  # 频谱幅值

# 3. IFFT：频域 -> 时域
ifft_result = np.fft.ifft(fft_result)
ifft_real = np.real(ifft_result)  # 取实部

# 4. 可视化
plt.figure(figsize=(12, 8))

# 原始时域信号
plt.subplot(3, 1, 1)
plt.plot(t, signal, label="Original Signal")
plt.title("Time Domain Signal")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.legend()

# FFT 结果（频谱）
plt.subplot(3, 1, 2)
plt.stem(freqs[:len(freqs)//2], magnitude[:len(freqs)//2])

plt.title("Frequency Domain (FFT)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")

# IFFT 恢复的信号
plt.subplot(3, 1, 3)
plt.plot(t, ifft_real, label="Reconstructed Signal")
plt.title("Reconstructed Time Domain Signal (IFFT)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.legend()

plt.tight_layout()
plt.show()
