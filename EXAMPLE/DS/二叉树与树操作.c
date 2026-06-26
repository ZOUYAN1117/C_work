/**
 * 文件: 二叉树与树操作.c
 * 描述: 包含一般二叉树 (BinNode)、二叉查找树 (BstNode) 及表达式树 (EtNode) 的操作。
 *       涵盖树节点构建、关联孩子、多种遍历 (前中后序)、高度/叶子计算、查找、删除与求值。
 */

#include <stdio.h>
#include <stdlib.h>

/* ==================== Part A：一般二叉树 ==================== */

/**
 * 结构体: BinNode - 一般二叉树节点结构定义
 * 成员：
 * - data: 存储结点的整型数值
 * - left: 指向左孩子节点的指针
 * - right: 指向右孩子节点的指针
 */
typedef struct BinNode {
    int data;
    struct BinNode *left;
    struct BinNode *right;
} BinNode;

/**
 * 新建一个一般二叉树节点 (左右孩子置空)
 * 参数：
 * - data: 节点的整型数值
 * 返回值：新建的节点指针；分配失败返回 NULL
 */
BinNode *btNewNode(int data)
{
    BinNode *p = (BinNode *)malloc(sizeof(BinNode));
    if (p == NULL)
        return NULL;
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/**
 * 把 child 挂接为 parent 节点的左孩子
 * 参数：
 * - parent: 父节点指针
 * - child: 子节点指针
 * 返回值：无
 */
void btAttachLeft(BinNode *parent, BinNode *child)
{
    parent->left = child;
}

/**
 * 把 child 挂接为 parent 节点的右孩子
 * 参数：
 * - parent: 父节点指针
 * - child: 子节点指针
 * 返回值：无
 */
void btAttachRight(BinNode *parent, BinNode *child)
{
    parent->right = child;
}

/**
 * 中序遍历一般二叉树 (左-根-右，空格分隔打印)
 * 参数：
 * - root: 二叉树根指针
 * 返回值：无
 */
void btInorder(BinNode *root)
{
    if (root == NULL)
        return;
    btInorder(root->left);
    printf("%d ", root->data);
    btInorder(root->right);
}

/**
 * 先序遍历一般二叉树 (根-左-右，空格分隔打印)
 * 参数：
 * - root: 二叉树根指针
 * 返回值：无
 */
void btPreorder(BinNode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    btPreorder(root->left);
    btPreorder(root->right);
}

/**
 * 后序遍历一般二叉树 (左-右-根，空格分隔打印)
 * 参数：
 * - root: 二叉树根指针
 * 返回值：无
 */
void btPostorder(BinNode *root)
{
    if (root == NULL)
        return;
    btPostorder(root->left);
    btPostorder(root->right);
    printf("%d ", root->data);
}

/**
 * 判断指定节点是否为叶子节点 (无左右孩子)
 * 参数：
 * - p: 指定节点指针
 * 返回值：1 表示为叶子节点，0 表示非叶子节点 (p 为 NULL 时也返回 0)
 */
int btIsLeaf(const BinNode *p)
{
    if (p == NULL)
        return 0;
    if (p->left == NULL && p->right == NULL)
        return 1;
    return 0;
}

/**
 * 计算一般二叉树的高度 (空树为 0，仅含根为 1)
 * 参数：
 * - root: 二叉树根指针
 * 返回值：树的高度
 */
int btHeight(const BinNode *root)
{
    int hl, hr;

    if (root == NULL)
        return 0;
    hl = btHeight(root->left);
    hr = btHeight(root->right);
    if (hl > hr)
        return hl + 1;
    return hr + 1;
}

/**
 * 统计一般二叉树的叶子节点个数
 * 参数：
 * - root: 二叉树根指针
 * 返回值：叶子节点个数
 */
int btCountLeaves(const BinNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return btCountLeaves(root->left) + btCountLeaves(root->right);
}

/**
 * 销毁二叉树并释放其所有节点的内存 (后序遍历释放)
 * 参数：
 * - root: 二叉树根指针
 * 返回值：无
 */
void btDestroy(BinNode *root)
{
    if (root == NULL)
        return;
    btDestroy(root->left);
    btDestroy(root->right);
    free(root);
}

/* ==================== Part B：二叉查找树（BST） ==================== */

/**
 * 结构体: BstNode - 二叉查找树节点结构定义
 * 成员：
 * - data: 存储结点的整型数值
 * - left: 指向左子树根节点的指针
 * - right: 指向右子树根节点的指针
 */
typedef struct BstNode {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

/**
 * 新建一个二叉查找树节点
 * 参数：
 * - data: 节点存储的整型数值
 * 返回值：新建节点指针；分配失败返回 NULL
 */
BstNode *bstNewNode(int data)
{
    BstNode *p = (BstNode *)malloc(sizeof(BstNode));
    if (p == NULL)
        return NULL;
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/**
 * 初始化二叉查找树为一棵空树
 * 参数：
 * - root: 指向查找树根指针的指针地址
 * 返回值：无
 */
void bstInit(BstNode **root)
{
    *root = NULL;
}

/**
 * 判断二叉查找树是否为空
 * 参数：
 * - root: 查找树根指针
 * 返回值：1 为空，0 非空
 */
int bstIsEmpty(const BstNode *root)
{
    return root == NULL;
}

/**
 * 按照 BST 插入规则插入新节点 (小放左，大或相等放右)
 * 参数：
 * - root: 查找树根指针
 * - data: 待插入的数据值
 * 返回值：指向插入新节点后的查找树根指针
 */
BstNode *bstInsert(BstNode *root, int data)
{
    if (root == NULL)
        return bstNewNode(data);
    if (data < root->data)
        root->left = bstInsert(root->left, data);
    else
        root->right = bstInsert(root->right, data);
    return root;
}

/**
 * 在二叉查找树中检索指定数据是否存在
 * 参数：
 * - root: 查找树根指针
 * - data: 待检索的数值
 * 返回值：1 存在，0 不存在
 */
int bstSearch(const BstNode *root, int data)
{
    if (root == NULL)
        return 0;
    if (data == root->data)
        return 1;
    if (data < root->data)
        return bstSearch(root->left, data);
    return bstSearch(root->right, data);
}

/**
 * 寻找二叉查找树中的最小节点 (最左下的叶子或半叶子节点)
 * 参数：
 * - root: 查找树根指针
 * 返回值：最小节点指针；若为空树则返回 NULL
 */
BstNode *bstMinNode(BstNode *root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

/**
 * 寻找二叉查找树中的最大节点 (最右下的叶子或半叶子节点)
 * 参数：
 * - root: 查找树根指针
 * 返回值：最大节点指针；若为空树则返回 NULL
 */
BstNode *bstMaxNode(BstNode *root)
{
    while (root != NULL && root->right != NULL)
        root = root->right;
    return root;
}

/**
 * 删除二叉查找树中值为 data 的节点，并维护查找树特性
 * 参数：
 * - root: 查找树根指针
 * - data: 待删除的整型数值
 * 返回值：指向删除后查找树的根指针
 */
BstNode *bstDelete(BstNode *root, int data)
{
    BstNode *m;

    if (root == NULL)
        return NULL;
    
    // 按值导航到指定结点
    if (data < root->data) {
        root->left = bstDelete(root->left, data);
        return root;
    }
    if (data > root->data) {
        root->right = bstDelete(root->right, data);
        return root;
    }
    
    // 找到了待删除节点，进行摘除
    // 情况 1: 左子树为空
    if (root->left == NULL) {
        BstNode *r = root->right;
        free(root);
        return r;
    }
    // 情况 2: 右子树为空
    if (root->right == NULL) {
        BstNode *r = root->left;
        free(root);
        return r;
    }
    // 情况 3: 左右子树均不为空，寻找右子树最小值替代它，然后递归删除该最小值
    m = bstMinNode(root->right);
    root->data = m->data;
    root->right = bstDelete(root->right, m->data);
    return root;
}

/**
 * 中序遍历二叉查找树 (有序输出)
 * 参数：
 * - root: 查找树根指针
 * 返回值：无
 */
void bstInorder(BstNode *root)
{
    if (root == NULL)
        return;
    bstInorder(root->left);
    printf("%d ", root->data);
    bstInorder(root->right);
}

/**
 * 先序遍历二叉查找树
 * 参数：
 * - root: 查找树根指针
 * 返回值：无
 */
void bstPreorder(BstNode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    bstPreorder(root->left);
    bstPreorder(root->right);
}

/**
 * 后序遍历二叉查找树
 * 参数：
 * - root: 查找树根指针
 * 返回值：无
 */
void bstPostorder(BstNode *root)
{
    if (root == NULL)
        return;
    bstPostorder(root->left);
    bstPostorder(root->right);
    printf("%d ", root->data);
}

/**
 * 计算二叉查找树的高度
 * 参数：
 * - root: 查找树根指针
 * 返回值：高度
 */
int bstHeight(const BstNode *root)
{
    int hl, hr;

    if (root == NULL)
        return 0;
    hl = bstHeight(root->left);
    hr = bstHeight(root->right);
    if (hl > hr)
        return hl + 1;
    return hr + 1;
}

/**
 * 统计二叉查找树的叶子结点个数
 * 参数：
 * - root: 查找树根指针
 * 返回值：叶子个数
 */
int bstCountLeaves(const BstNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return bstCountLeaves(root->left) + bstCountLeaves(root->right);
}

/**
 * 深度优先输出查找树中的每个叶子节点的值与其对应深度 (根深度为 1)
 * 参数：
 * - root: 查找树根指针
 * - depth: 当前节点所在深度层级
 * 返回值：无
 */
void bstReportLeavesWithDepth(BstNode *root, int depth)
{
    if (root == NULL)
        return;
    bstReportLeavesWithDepth(root->left, depth + 1);
    if (root->left == NULL && root->right == NULL)
        printf("%d %d\n", root->data, depth);
    bstReportLeavesWithDepth(root->right, depth + 1);
}

/**
 * 销毁整个二叉查找树，释放内存
 * 参数：
 * - root: 查找树根指针
 * 返回值：无
 */
void bstDestroy(BstNode *root)
{
    if (root == NULL)
        return;
    bstDestroy(root->left);
    bstDestroy(root->right);
    free(root);
}

/* ==================== Part C：表达式树 ==================== */

/**
 * 结构体: EtNode - 表达式二叉树节点结构定义
 * 成员：
 * - isOp: 1 表示该节点为运算符，0 表示为数值操作数
 * - value: 当 isOp 为 0 时，存储其整型数值
 * - op: 当 isOp 为 1 时，存储其字符运算符 (如 '+', '-', '*', '/')
 * - left: 指向左子树 (运算数或子表达式) 的指针
 * - right: 指向右子树 (运算数或子表达式) 的指针
 */
typedef struct EtNode {
    int isOp;
    int value;
    char op;
    struct EtNode *left;
    struct EtNode *right;
} EtNode;

/**
 * 新建一个数值操作数叶子节点
 * 参数：
 * - v: 节点整型数值
 * 返回值：新建表达式树节点指针
 */
EtNode *etNewNum(int v)
{
    EtNode *p = (EtNode *)malloc(sizeof(EtNode));
    p->isOp = 0;
    p->value = v;
    p->op = '\0';
    p->left = NULL;
    p->right = NULL;
    return p;
}

/**
 * 新建一个运算符节点，并将左右子树关联为子表达式
 * 参数：
 * - op: 字符型运算符 ('+', '-', '*', '/')
 * - l: 左子树节点指针
 * - r: 右子树节点指针
 * 返回值：新建的运算符节点指针
 */
EtNode *etNewOp(char op, EtNode *l, EtNode *r)
{
    EtNode *p = (EtNode *)malloc(sizeof(EtNode));
    p->isOp = 1;
    p->op = op;
    p->value = 0;
    p->left = l;
    p->right = r;
    return p;
}

/**
 * 后续遍历递归求解表达式树的代数计算数值 (除法按 C 整除计算)
 * 参数：
 * - root: 表达式树根节点指针
 * 返回值：计算最终得到的数值结果
 */
int etEval(EtNode *root)
{
    int a, b;

    // 叶子节点直接返回数据值
    if (root->isOp == 0)
        return root->value;
    
    // 分别计算左右子表达式的值
    a = etEval(root->left);
    b = etEval(root->right);
    
    // 执行运算
    if (root->op == '+')
        return a + b;
    if (root->op == '-')
        return a - b;
    if (root->op == '*')
        return a * b;
    if (root->op == '/')
        return a / b;
    return 0;
}

/**
 * 释放整棵表达式树的内存空间
 * 参数：
 * - root: 表达式树根节点指针
 * 返回值：无
 */
void etFree(EtNode *root)
{
    if (root == NULL)
        return;
    etFree(root->left);
    etFree(root->right);
    free(root);
}
