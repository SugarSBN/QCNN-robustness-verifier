# 关于试验细节的一些说明

## Polygon的选择

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324092620358.png" alt="image-20220324092620358" style="zoom:50%;" />

这部分，center是一个PureState，然后我选取了一个四边形。即四个量子态：

* 将center的第0个qubit作用门$RY(eps)$得到的量子态$|q_0\rangle$
* 将center的第1个qubit作用门$RY(eps)$得到的量子态$|q_1\rangle$
* 将center的第0个qubit作用门$RY(-eps)$得到的量子态$|q_2\rang$
* 将center的第1个qubit作用门$RY(-eps)$得到的量子态$|q_3\rangle$

为什么这么取呢？实际上，将量子态作用门$I\otimes I\otimes ...\otimes I\otimes RY$并不对应着绕着轴$I\otimes I\otimes ...\otimes I\otimes RY$进行旋转？（这里我不清楚，我就认为他不对）

但是可以换一种理解方式，因为作用门后量子态还是纯态，所以一定是绕着某个轴旋转的。（考虑之前推导的$|\psi\rang$对应的向量$\overrightarrow{v}$）

因为高维空间的旋转并不是很好理解，可以再换一种想法。把量子态既然看作向量了，由于我们取的是旋转一个负角度，作用门的本质是向量中一些分量变大，一些分量减小；而作用负数RY正好可以使得原来减小的分量变大，原来变大的分量减小。所以实际上，center量子态一定在$|q_0\rangle$和$|q_2\rangle$的连线上。

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324094053790.png" alt="image-20220324094053790" style="zoom:50%;" />

想法就是虽然我不知道是绕着哪个轴旋转的，但它一定是个旋转。数字上，就是将向量一些分量变大一些分量减小。由于对称性，center态一定是被$|q_0\rangle,...|q_3\rangle$包围的，这就足够了。

## 域的验证

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324094434382.png" alt="image-20220324094434382" style="zoom:50%;" />

verify函数非常简单，就是给出一个类ans，然后对polygon的四个顶点分类，返回这四个顶点是否都被分到了ans类里。

## 鲁棒界的确定

一旦四个顶点都被verify了，就可以开始计算鲁棒域。

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324094725339.png" alt="image-20220324094725339" style="zoom:50%;" />

我们可以先考虑下对于四边形的一条边$q_0q_1$，和center组成的四面体。（当然这是为了直观理解，高维空间并不好定义几何体）

可以确定的是，我们需要做的事情，就是寻找：
$$
max_{\alpha\in[0,1]}\frac{center\cdot (\alpha|q_0\rang + (1-\alpha)|q_1\rang)}{||\alpha|q_0\rang + (1-\alpha)|q_1\rang||}=cos\theta
$$
因为我们需要寻找最小的$\theta$。如果对于这条边，找到了最小的$\theta$，再对剩下三条边都找一下，然后取最小值，就可以通过之前的理论推导得到一个$\varepsilon$。

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324095043171.png" alt="image-20220324095043171" style="zoom:50%;" />

这部分的数值计算有些费解。首先，在基$\{X,Y,Z,I\}^{\otimes n}-I^{\otimes n}$这个基下，是不满足纯态的$|\overrightarrow{v}|=1$的，我们需要对基做归一化。

其实归一化后的基是$\sqrt{2^n-1}(\{X,Y,Z,I\}^{\otimes n}-I^{\otimes n})$。前面系数是怎么得来的？可以看一下简单推导：
$$
原始情况下：\\
\rho=\frac{1}{2^n}(I+\overrightarrow{v}\cdot\overrightarrow{\sigma})\\
Tr(\sigma_i\sigma_j)=2^n\delta_{ij}\\
然后就有：\\
Tr(\rho^2)=\frac{1}{4^n}(2^n+|\overrightarrow{v}|^22^n)\\
其中|\overrightarrow{v}|^2乘的2^n就是Tr(\sigma_i\sigma_j)=2^n\delta_{ij}前的那个2^n.\\
因为我们想要Tr(\rho^2)=1\Leftrightarrow |\overrightarrow{v}|^2=1\\
所以就要使得Tr(\sigma_i\sigma_j)=(4^n-2^n)\delta_{ij}\\
所以基前面需要乘一个系数\sqrt{2^n-1}
$$
然后此时有：
$$
Fidelity(\psi_1,\psi_2)=|\lang \psi_1|\psi_2|\rang|^2\\
=\frac{1+(2^n-1)\overrightarrow{v_1}\cdot\overrightarrow{v_2}}{2^n}
$$
回到之前需要最大化的值：
$$
max_{\alpha\in[0,1]}\frac{center\cdot (\alpha|q_0\rang + (1-\alpha)|q_1\rang)}{||\alpha|q_0\rang + (1-\alpha)|q_1\rang||}=cos\theta
$$
由于我懒得求导，会发现分母$||\alpha|q_0\rang + (1-\alpha)|q_1\rang||\geq\frac{1}{\sqrt{2}}$的（因为转的比较小，$|q_0\rang$和$|q_1\rang$成锐角），所以我直接把上面的结果算作：
$$
\sqrt{2}*max(cos(center,|q_0\rang),cos(center,|q_1\rang))
$$
也就有了cal()函数。

然后robust_bound函数就是对每条边都cal了一下，最后取个最大的$cos\theta$，最后计算出bound：
$$
\varepsilon=1-maxFidelity=1-max\frac{1+(2^n-1)cos\theta}{2^n}
$$

## 实验的结果

前面都是原理性说明，我不是很有信心表达清楚。但是我们可以看一下结果。

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324101047133.png" alt="image-20220324101047133" style="zoom:50%;" />

可以看一下我取点的随机策略，我随机生成了一个角度phi，一个target qubit，一个gate(RX, RY, RZ)。然后将gate作用在target qubit上转phi角度。

为了增加数据的强度，如果产生的状态和center态的distance离得太远（差0.01以上），则我会重新生成。也就是说，sample的点一定会特别靠近验证出来的robust边界。

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324101606378.png" alt="image-20220324101606378" style="zoom:50%;" /><img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324101705445.png" alt="image-20220324101705445" style="zoom:50%;" />





可以看到，对第一个center态，我随即抽取了100个sample，都得到了验证。而且数据中不乏离robust bound特别近的点（distance = 0.1394等）

而我也输出了官老师lemma1的robust bound，对于第一个样本点guan老师的robust bound只给了0.016。

----

如果不输出详细的sample过程，我们可以对不同的center态进行random sampling check：

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324102744103.png" alt="image-20220324102744103" style="zoom:50%;" /><img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324102825825.png" alt="image-20220324102825825" style="zoom:50%;" />

由于每个center都需要sample 100个点，比较耗时间，所以我选择了10个不同的center态，都得到了验证。

这里可能有疑问，为什么有时候验证出来robust bound是负数？这其实很显然，因为之前求max$cos\theta$时，我直接放缩到$\sqrt{2}$，可能会过大了。

其次

<img src="C:\Users\NaiDeKudasai\AppData\Roaming\Typora\typora-user-images\image-20220324103050157.png" alt="image-20220324103050157" style="zoom:50%;" />

如果对于一个eps，我们的polygon四个顶点并没有被完全分入同一个类怎么办？为了节省时间，我使用了最简单朴素的方法。

即我把初始eps设成1.6，然后如果没被验证，就把eps - 0.05，缩小四边形直到能验证了为止。因此会发现验证出来的robust bound都是一些离散的值。

当然这是为了节省时间，也可以缩短步长或者做更精细的启发式验证。