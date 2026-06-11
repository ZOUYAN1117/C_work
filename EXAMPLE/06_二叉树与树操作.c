/*
 * 二叉树与树操作（第五次作业：树）
 *
 * 【功能清单】
 *   Part A 一般二叉树 BinNode
 *     btNewNode · btAttachLeft · btAttachRight
 *     btInorder · btPreorder · btPostorder
 *     btIsLeaf · btHeight · btCountLeaves · btDestroy
 *   Part B 二叉查找树 BstNode
 *     bstNewNode · bstInit · bstIsEmpty
 *     bstInsert · bstSearch · bstMinNode · bstMaxNode · bstDelete
 *     bstInorder · bstPreorder · bstPostorder
 *     bstHeight · bstCountLeaves · bstReportLeavesWithDepth · bstDestroy
 *   Part C 表达式树 EtNode
 *     etNewNum · etNewOp · etEval · etFree
 *
 * 用法：把需要的结构体和函数复制到你的 .c 文件里。
 * 约定：返回 1 表示“是/成功”，返回 0 表示“否/失败”（与 01~05 库相同）。
 */

#include <stdio.h>
#include <stdlib.h>

/* ==================== Part A：一般二叉树 ==================== */

typedef struct BinNode {
    int data;
    struct BinNode *left;
    struct BinNode *right;
} BinNode;

/*
 * 功能：新建一个结点，左右孩子先为空
 * 返回：新结点指针；malloc 失败返回 NULL
 *
 * 使用示例：
 *   BinNode *a = btNewNode(1);
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

/*
 * 功能：把 child 挂到 parent 的左边
 * 返回：无
 *
 * 使用示例：
 *   btAttachLeft(parent, child);
 */
void btAttachLeft(BinNode *parent, BinNode *child)
{
    parent->left = child;
}

/*
 * 功能：把 child 挂到 parent 的右边
 * 返回：无
 *
 * 使用示例：
 *   btAttachRight(parent, child);
 */
void btAttachRight(BinNode *parent, BinNode *child)
{
    parent->right = child;
}

/*
 * 功能：中序遍历（左-根-右），用 printf 输出
 * 返回：无
 *
 * 使用示例（先建好树再遍历，下同）：
 *   BinNode *r = btNewNode(1);
 *   BinNode *a = btNewNode(2), *b = btNewNode(3);
 *   BinNode *c = btNewNode(4), *d = btNewNode(5);
 *   btAttachLeft(r, a);  btAttachRight(r, b);
 *   btAttachLeft(a, c);  btAttachRight(a, d);
 *   btInorder(r);        输出：4 2 5 1 3
 */
void btInorder(BinNode *root)
{
    if (root == NULL)
        return;
    btInorder(root->left);
    printf("%d ", root->data);
    btInorder(root->right);
}

/*
 * 功能：先序遍历（根-左-右），用 printf 输出
 * 返回：无
 *
 * 使用示例：
 *   btPreorder(r);       输出：1 2 4 5 3
 */
void btPreorder(BinNode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    btPreorder(root->left);
    btPreorder(root->right);
}

/*
 * 功能：后序遍历（左-右-根），用 printf 输出
 * 返回：无
 *
 * 使用示例：
 *   btPostorder(r);      输出：4 5 2 3 1
 */
void btPostorder(BinNode *root)
{
    if (root == NULL)
        return;
    btPostorder(root->left);
    btPostorder(root->right);
    printf("%d ", root->data);
}

/*
 * 功能：判断结点是否为叶子（无左右孩子）
 * 返回：1 是叶子，0 否（p 为 NULL 时返回 0）
 *
 * 使用示例：
 *   if (btIsLeaf(p)) printf("是叶子\n");
 */
int btIsLeaf(const BinNode *p)
{
    if (p == NULL)
        return 0;
    if (p->left == NULL && p->right == NULL)
        return 1;
    return 0;
}

/*
 * 功能：求树的高度
 * 返回：空树 0，只有根为 1
 *
 * 使用示例：
 *   int h = btHeight(r);
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

/*
 * 功能：统计叶子结点个数
 * 返回：叶子个数
 *
 * 使用示例：
 *   int n = btCountLeaves(r);
 */
int btCountLeaves(const BinNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return btCountLeaves(root->left) + btCountLeaves(root->right);
}

/*
 * 功能：释放整棵树（后序释放）
 * 返回：无
 *
 * 使用示例：
 *   btDestroy(r);
 *   r = NULL;
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

typedef struct BstNode {
    int data;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

/*
 * 功能：新建 BST 结点（一般由 bstInsert 内部调用）
 * 返回：新结点指针；malloc 失败返回 NULL
 *
 * 使用示例：
 *   BstNode *p = bstNewNode(50);
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

/*
 * 功能：把根指针置为空树
 * 返回：无
 *
 * 使用示例：
 *   BstNode *root = NULL;
 *   bstInit(&root);
 */
void bstInit(BstNode **root)
{
    *root = NULL;
}

/*
 * 功能：判断 BST 是否为空
 * 返回：1 空，0 非空
 *
 * 使用示例：
 *   if (bstIsEmpty(root)) printf("空树\n");
 */
int bstIsEmpty(const BstNode *root)
{
    return root == NULL;
}

/*
 * 功能：按 BST 规则插入（小放左，大放右，相等放右）
 * 返回：插入后的根指针（可能变）
 *
 * 使用示例：
 *   BstNode *root = NULL;
 *   bstInit(&root);
 *   root = bstInsert(root, 50);
 *   root = bstInsert(root, 30);
 *   root = bstInsert(root, 70);
 *   root = bstInsert(root, 20);
 *   root = bstInsert(root, 40);
 *   root = bstInsert(root, 60);
 *   root = bstInsert(root, 80);
 *   root = bstInsert(root, 10);
 *   root = bstInsert(root, 25);
 *   root = bstInsert(root, 35);
 *   root = bstInsert(root, 45);
 *   root = bstInsert(root, 55);
 *
 *   按上述顺序插入后的树形（高度 4，叶子 6 个）：
 *                    50
 *                   /  \
 *                 30    70
 *                /  \   / \
 *              20   40 60  80
 *             / \  / \   \
 *           10 25 35 45  55
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

/*
 * 功能：在 BST 中查找 data
 * 返回：1 找到，0 未找到
 *
 * 使用示例：
 *   if (bstSearch(root, 40)) printf("找到了\n");
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

/*
 * 功能：找最小结点（最左下）
 * 返回：最小结点指针；空树返回 NULL
 *
 * 使用示例：
 *   BstNode *minp = bstMinNode(root);
 *   if (minp) printf("%d\n", minp->data);
 */
BstNode *bstMinNode(BstNode *root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

/*
 * 功能：找最大结点（最右下）
 * 返回：最大结点指针；空树返回 NULL
 *
 * 使用示例：
 *   BstNode *maxp = bstMaxNode(root);
 */
BstNode *bstMaxNode(BstNode *root)
{
    while (root != NULL && root->right != NULL)
        root = root->right;
    return root;
}

/*
 * 功能：删除值为 data 的结点
 * 返回：删除后的根指针
 *
 * 使用示例：
 *   root = bstDelete(root, 30);
 */
BstNode *bstDelete(BstNode *root, int data)
{
    BstNode *m;

    if (root == NULL)
        return NULL;
    if (data < root->data) {
        root->left = bstDelete(root->left, data);
        return root;
    }
    if (data > root->data) {
        root->right = bstDelete(root->right, data);
        return root;
    }
    if (root->left == NULL) {
        BstNode *r = root->right;
        free(root);
        return r;
    }
    if (root->right == NULL) {
        BstNode *r = root->left;
        free(root);
        return r;
    }
    m = bstMinNode(root->right);
    root->data = m->data;
    root->right = bstDelete(root->right, m->data);
    return root;
}

/*
 * 功能：中序遍历 BST，用 printf 输出
 * 返回：无
 *
 * 使用示例（用 bstInsert 示例中的插入序列建好 root）：
 *   bstInorder(root);
 *   输出：10 20 25 30 35 40 45 50 55 60 70 80
 */
void bstInorder(BstNode *root)
{
    if (root == NULL)
        return;
    bstInorder(root->left);
    printf("%d ", root->data);
    bstInorder(root->right);
}

/*
 * 功能：先序遍历 BST，用 printf 输出
 * 返回：无
 *
 * 使用示例：
 *   bstPreorder(root);
 *   输出：50 30 20 10 25 40 35 45 70 60 55 80
 */
void bstPreorder(BstNode *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    bstPreorder(root->left);
    bstPreorder(root->right);
}

/*
 * 功能：后序遍历 BST，用 printf 输出
 * 返回：无
 *
 * 使用示例：
 *   bstPostorder(root);
 *   输出：10 25 20 35 45 40 30 55 60 80 70 50
 */
void bstPostorder(BstNode *root)
{
    if (root == NULL)
        return;
    bstPostorder(root->left);
    bstPostorder(root->right);
    printf("%d ", root->data);
}

/*
 * 功能：求 BST 高度
 * 返回：空树 0，只有根为 1
 *
 * 使用示例：
 *   int h = bstHeight(root);
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

/*
 * 功能：统计 BST 叶子个数
 * 返回：叶子个数
 *
 * 使用示例：
 *   int n = bstCountLeaves(root);
 */
int bstCountLeaves(const BstNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return bstCountLeaves(root->left) + bstCountLeaves(root->right);
}

/*
 * 功能：输出每个叶子的“值 深度”（根深度为 1），每行一个
 * 返回：无
 *
 * 使用示例：
 *   bstReportLeavesWithDepth(root, 1);
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

/*
 * 功能：释放整棵 BST
 * 返回：无
 *
 * 使用示例：
 *   bstDestroy(root);
 *   root = NULL;
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

typedef struct EtNode {
    int isOp;
    int value;
    char op;
    struct EtNode *left;
    struct EtNode *right;
} EtNode;

/*
 * 功能：新建数字叶子结点
 * 返回：新结点指针
 *
 * 使用示例：
 *   EtNode *n = etNewNum(3);
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

/*
 * 功能：新建运算符结点，左右子树为 l、r
 * 返回：新结点指针
 *
 * 使用示例：
 *   EtNode *t = etNewOp('+', etNewNum(2), etNewNum(3));
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

/*
 * 功能：后序求值（支持 + - * /，除法为整除）
 * 返回：表达式的值
 *
 * 使用示例：
 *   EtNode *t = etNewOp('+', etNewNum(2), etNewOp('*', etNewNum(3), etNewNum(4)));
 *   int v = etEval(t);   v 为 14
 */
int etEval(EtNode *root)
{
    int a, b;

    if (root->isOp == 0)
        return root->value;
    a = etEval(root->left);
    b = etEval(root->right);
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

/*
 * 功能：释放表达式树
 * 返回：无
 *
 * 使用示例：
 *   etFree(t);
 *   t = NULL;
 */
void etFree(EtNode *root)
{
    if (root == NULL)
        return;
    etFree(root->left);
    etFree(root->right);
    free(root);
}
