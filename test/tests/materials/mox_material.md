# 验证

##MOX热导率

公式：
$$
\lambda = \frac{1-p}{1+0.5p}[\frac{1}{2.713x+3.583\times10^{-1}\times z_1+6.317\times10^{-2}\times z_2+1.595\times 10{-2}+(-2.625x+2.493)\times 10^{-4}T}+\frac{1.54\times 10^{11}}{T^{5/2}exp(\frac{-1.522\times 10^4}{T}}]
$$

其中$\lambda$是热导率，$p$是孔隙度，x是偏析度$MO_{2.00-x}$，$z_1$是Am的含量，$z_2$是Np的含量。

条件： p= 0（待定），Np=Am= 1.6%。温度范围是500k-2300K

|                          论文中结果                          |                      moose中MOXThermal                       |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| ![image-20230206161422071](https://cdn.jsdelivr.net/gh/wangzhaohao/markdown-img@main/uPic/2023/tZ7itp_s11nfl_image-20230206161422071.png) | ![image-20230206161707823](https://cdn.jsdelivr.net/gh/wangzhaohao/markdown-img@main/uPic/2023/Z3kDky_image-20230206161707823.png) |

可以看出两者结果相同。
