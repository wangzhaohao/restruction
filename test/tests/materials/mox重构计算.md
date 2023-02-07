# mox重构计算

## 气孔的迁移速度

论文中给的方程是
$$
v=5\times10^{-16}(0.988 +6.395\times10^{-6}T+3.543\times10^{-9}T^2+3\times10^{-12}T^3)\times T^{-\frac{5}{2}}\triangle H p_0exp(-\triangle H/RT)\frac{dT}{dr}
$$
其中$p_0 \triangle H$可以从下表获得

<table>
  <caption>UO2 vapour pressure data</caption>
</table>

|   T(K)    | ln $p_0$($dynes/cm^2$) | $\triangle H$(Ergs/mole) |
| :-------: | :--------------------: | :----------------------: |
| 1500~2000 |        33.7085         |   $5.98\times 10^{12}$   |
| 2000~2200 |      $34.8107a)$       | $6.17\times 10^{12} a)$  |
| 2200~2800 |        35.8130         |   $6.35\times 10^{12}$   |

a) 通过插值

假设温度分布是抛物线形式分布，中心温度是2800K表面温度是900K。RZ坐标系中，温度分布应该是$T= -7.6\times 10^7 r^2 +2800\space (0<r<5\times10^{-3})$，通过此得到的pore的迁移速度分布曲线如下：

![image-20230204092135942](https://cdn.jsdelivr.net/gh/wangzhaohao/markdown-img@main/uPic/2023/niHQDZ_image-20230204092135942.png)

![image-20230204092206471](https://cdn.jsdelivr.net/gh/wangzhaohao/markdown-img@main/uPic/2023/AWMoqj_image-20230204092206471.png)

![image-20230204092234245](https://cdn.jsdelivr.net/gh/wangzhaohao/markdown-img@main/uPic/2023/KVABcJ_Ag1K0f_image-20230204092234245.png)

发现和文献中趋势相同但是数值不同，使用计算机手动算发现程序中没有错误。程序中注意了RZ坐标系。

程序目前无法验证的问题出现在功率如何输入。
