/*
 * AVL树的代码实现
 */

#include <stdlib.h>
#include "avl-tree.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/*
 * AVL树的节点结构
 */
typedef struct _AVLTreeEntry AVLTreeEntry;

struct _AVLTreeEntry {
    int bf;                 /* 平衡因子*/
    AVLTreeValue data;      /* 数据元素 */
    AVLTreeEntry *left;     /* 左孩子 */
    AVLTreeEntry *right;    /* 右孩子 */
};

struct _AVLTree {
    AVLTreeEntry *root;         /* 根结点 */
    AVLTreeCompareFunc cmp;     /* 节点元素比较大小函数 */
};

AVLTree *avltree_new(AVLTreeCompareFunc cmp)
{
    AVLTree *avltree;

    avltree = (AVLTree *) malloc(sizeof(AVLTree));
    if (!avltree) {
        return NULL;
    }

    avltree->root = NULL;
    avltree->cmp  = cmp;

    return avltree;
}

/**
 * subtree_free     销毁子树
 * 
 * @param root      子树根结点
 */
static void subtree_free(AVLTreeEntry *root)
{
    if (!root) {
        return;
    }
    
    subtree_free(root->left);
    subtree_free(root->right);
    
    free(root);
}

void avltree_free(AVLTree *avltree)
{
    subtree_free(avltree->root);
}

/**
 * bstee_add            插入节点
 *
 * @param avltree        AVL树
 * @param value         待插入的元素值
 * @return              插入成功，则返回非0值，
 *                      失败（内存分配失败），则返回0。
 */
int avltree_add(AVLTree *avltree, AVLTreeValue value)
{
    
}

/**
 * subtree_find         查找子树中是否存在特定节点
 *
 * @param root          子树根结点
 * @param value         待查找的值
 * @param cmp           节点元素比较大小函数
 * @return              存在节点，其值等于value，则返回非0值，
 *                      否则，返回0。
 */
static int subtree_find(AVLTreeEntry *root,
                        AVLTreeValue value,
                        AVLTreeCompareFunc cmp)
{
    while (root != NULL && cmp(value, root->data) != 0) {
        if (cmp(value, root->data) < 0) {
            root = root->left;

        } else {
            root = root->right;
        }
    }

    /*
     * 存在匹配节点，则返回1，
     * 不存在，则返回0。
     */
    return root != NULL;
}

int avltree_find(AVLTree *avltree, AVLTreeValue value)
{
    return subtree_find(avltree->root, value, avltree->cmp);
}

/**
 * avltree_del           删除节点
 *
 * @param avltree        AVL树
 * @param value         待删除的节点元素值
 * @return              若删除成功，则返回非0值，
 *                      否则，AVL树中不存在该节点，返回0。
 */
int avltree_del(AVLTree *avltree, AVLTreeValue value);

static int subtree_depth(AVLTreeEntry *root)
{
    if (!root) {
        return 0;
    }

    return MAX(subtree_depth(root->left), subtree_depth(root->right)) + 1;
}

int avltree_depth(AVLTree *avltree)
{
    return subtree_depth(avltree->root);
}

int avltree_is_empty(AVLTree *avltree)
{
    return avltree->root == NULL;
}

#endif /* BULLET_AVLTREE_H */
