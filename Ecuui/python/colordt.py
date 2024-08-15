import numpy as np
import matplotlib.pyplot as plt

# 生成隨機的點和方向
np.random.seed(0)
n = 100
x = np.random.rand(n)
y = np.random.rand(n)
direction = np.random.rand(n) * 2 * np.pi  # 0 到 2*pi 之間的隨機角度

# 分別獲得每個點的顏色
colors = np.array(['r', 'g', 'b'])  # 三種顏色
color_indices = np.digitize(direction, bins=[0, np.pi/3, 2*np.pi/3, np.pi*2])
for ii in list([2, 3, 5, 6, 10, 13, 22]):
    color_indices[ii] = 0

# 繪製點分布圖
plt.figure(figsize=(8, 6))
for i in range(len(colors)):
    plt.scatter(x[color_indices == i], y[color_indices == i],
                color=colors[i], label=f'Direction {i+1}')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Scatter Plot with Directional Colors')
plt.legend()
plt.grid(True)
# plt.xlim(0, 100)
# plt.ylim(0, 100)
plt.show()
