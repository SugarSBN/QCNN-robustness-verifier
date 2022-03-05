'''
Author: SuBonan
Date: 2022-03-05 10:03:09
LastEditTime: 2022-03-05 10:18:20
FilePath: \QCNN\plt_show.py
Github: https://github.com/SugarSBN
これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
'''
'''
Author: SuBonan
Date: 2022-03-05 10:03:09
LastEditTime: 2022-03-05 10:03:11
FilePath: \QCNN\plt_show.py
Github: https://github.com/SugarSBN
これなに、これなに、これない、これなに、これなに、これなに、ねこ！ヾ(*´∀｀*)ﾉ
'''
import matplotlib.pyplot as plt
import numpy as np
import re
f = open("images.txt")
s1 = f.readline()

images = []
for i in range(1263):
    rua = []
    s1 = f.readline()
    s = re.split(' ', s1)
    for j in s:
        if j != '\n':
            rua.append(float(j))
    images.append(rua)

t = 0
for i in range(9):
    plt.subplot(3, 3, i + 1)
    plt.imshow(np.array(images[i]).reshape(16, 16), cmap = 'gray')
plt.colorbar()
plt.show()
