1. 二叉树的定义
2. 二叉树的分类（6种）
   1. 普通二叉树
   2. 扩展二叉树
   3. 斜树
   4. 完全二叉树
   5. 满二叉树
3. 二叉树的特点（5种）
   1. 第i层最多有2^(i - 1)个结点
   2. 深度为k的二叉树至多又2^k - 1个结点(i >= 1)
   3. 终端结点为n0，度为2的结点为n2，则n0 = n2 + 1
   4. 具有n个结点的完全二叉树的深度为[log2n ] + 1
   5. 规则：
      1. i = 1 ==> 双亲[i / 2]
      2. 2i <= n ==> 左孩子为2i
      3. 2i + 1 <= n ==> 右孩子为2i + 1
4. 存储结构
   1. 顺序存储
   2. 链式存储
5. 遍历
   1. 基本遍历法
      1. 先序（理论 + 代码【**递归** + 非递归】）
      2. 中序（理论 + 代码【**递归** + 非递归】）
      3. 后序 （理论 + 代码【**递归** + 非递归】）
      4. 层序 （理论 + 代码【**非递归**】）
   2. 推导遍历结果
      1. 前序 + 中序（理论）
      2. 中序 + 后序（理论）
6. 二叉树的线索化（理论 + 代码）
7. 附加（代码）
   1. 统计二叉树结点的个数
      1. 统计所有结点的个数
      2. 统计度为1的结点的个数
      3. 统计度为2的结点的个数