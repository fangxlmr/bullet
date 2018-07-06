/*
 * AVL树的代码实现
 */

#include <stdlib.h>
#include "avl-tree.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/*
 * AVL树的节点结构
 */
typedef struct _AVLTreeNode AVLTreeNode;

struct _AVLTreeNode {
    AVLTreeValue data;      /* 数据元素 */
    int height;             /* 平衡因子 */
    AVLTreeNode *left;      /* 左孩子 */
    AVLTreeNode *right;     /* 右孩子 */
};

struct _AVLTree {
    AVLTreeNode *root;          /* 根结点 */
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
static void subtree_free(AVLTreeNode *root)
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
 * height           求子树的高度
 *
 * @param node      子树根结点
 * @return          返回子树的高度。如果节点位空，则返回0。
 */
static int height(AVLTreeNode *node)
{
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

/**
 * rr_rotation          右右旋转（左旋）
 *
 * @param node          最小不平衡子树根结点的二级指针
 * @note                新节点插入到根结点右子树的右子树
 */
static void rr_rotation(AVLTreeNode **node)
{
    AVLTreeNode *root;
    AVLTreeNode *tmp;

    root = *node;
    tmp = root->right;          /* 保存根结点的右子树 */
    root->right = tmp->left;    /* 根结点的右子树重接为右子树的左子树 */
    tmp->left = root;

    /*
     * 更新节点树的深度
     */
    root->height = MAX(height(root->left), height(root->right)) + 1;
    tmp->height  = MAX(height(tmp->left),  height(tmp->right)) + 1;

    *node = tmp;           /* 更新根结点 */
}

/**
 * ll_rotation         左左情况（右旋）
 *
 * @param node         最小不平衡子树根结点的二级指针
 * @note               新节点插入到根结点左子树的左子树
 */
static void ll_rotation(AVLTreeNode **node)
{
    AVLTreeNode *root;
    AVLTreeNode *tmp;

    root = *node;
    tmp = root->left;           /* 保存根结点的左子树 */
    root->left = tmp->right;    /* 根结点的左子树重接为左子树的右子树 */
    tmp->right = root;
    
    /*
     * 更新节点的子树深度
     */
    root->height = MAX(height(root->left), height(root->right)) + 1;
    tmp->height  = MAX(height(tmp->left),  height(tmp->right)) + 1;
    
    *node = tmp;           /* 更新根结点 */
}

/**
 * lr_rotation      左右情况（左右双旋）
 *
 * @param node      最小不平衡子树的二级指针
 * @note            新节点插入到根结点左子树的右子树
 */
static void lr_rotation(AVLTreeNode **node)
{
    /*
     * lr的情况：
     * 对于node->left，是rr情况，进行rr_rotation，
     */
    rr_rotation(&(*node)->left);
    /*
     * ll旋转之后，对于node，是ll情况，进行ll_rotation。
     */
    ll_rotation(node);
}

/**
 * rl_rotation      左右情况（左右双旋）
 *
 * @param node      最小不平衡子树的二级指针
 * @note            新节点插入到根结点右子树的左子树
 */
static void rl_rotation(AVLTreeNode **node)
{
    /*
     * rl的情况：
     * 对于node->right，是ll情况，进行ll_rotation，
     */
    ll_rotation(&(*node)->right);
    /*
     * ll旋转之后，对于node，是rr情况，进行rr_rotation。
     */
    rr_rotation(node);
}

/**
 * subtree_add      添加新节点
 *
 * @param node      根结点的二级指针
 * @param value     待插入的元素值
 * @param cmp       节点元素比较大小函数
 * @return          插入成功，则返回非0值。插入失败（内存分配失败，或
 *                  已存在相同元素），则返回0。
 */
static int subtree_add(AVLTreeNode **node, AVLTreeValue value,
                       AVLTreeCompareFunc cmp)
{
    AVLTreeNode *new_node;

    if (*node == NULL) {
        /*
         * 新建并插入节点
         */
        new_node = (AVLTreeNode *) malloc(sizeof(AVLTreeNode));

        if (!new_node) {
            return 0;
        }
        new_node->data   = value;
        new_node->height = 1;
        new_node->left   = NULL;
        new_node->right  = NULL;

        *node = new_node;   /* 插入新节点 */

        /*
         * 插入左子树
         */
    } else if (cmp(value, (*node)->data) < 0) {
        subtree_add(&(*node)->left, value, cmp);

        /* 失去平衡，调整使其重新平衡 */
        if (height((*node)->left) - height((*node)->right) == 2) {
            if (cmp(value, (*node)->left) < 0) {
                ll_rotation(node);
            } else {
                lr_rotation(node);
            }
        }

        /*
         * 插入右子树
         */
    } else if (cmp(value, (*node)->data) > 0) {
        subtree_add(&(*node)->right, value, cmp);

        if (height((*node)->right) - height((*node)->left) == 2) {
            if (cmp(value, (*node)->data) < 0) {
                rl_rotation(node);
            } else {
                rr_rotation(node);
            }
        }

        /*
         * 重复节点，忽略
         */
    } else {
        return 0;
    }

    /* 更新节点高度 */
    (*node)->height = MAX(height((*node)->left), height((*node)->right)) + 1;
    return 1;
}

int avltree_add(AVLTree *avltree, AVLTreeValue value)
{
    return subtree_add(&avltree->root, value, avltree->cmp);
}

int avltree_find(AVLTree *avltree, AVLTreeValue value)
{
    AVLTreeNode *node;
    AVLTreeCompareFunc cmp;

    node = avltree->root;
    cmp  = avltree->cmp;

    while (node != NULL && cmp(value, node->data) != 0) {
        if (cmp(value, node->data) < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    /*
     * 存在匹配节点，则返回1，
     * 不存在，则返回0。
     */
    return node != NULL;
}

/**
 * subree_del       删除节点
 *
 * @param node      待删除节点子树的根结点二级指针
 * @param value     匹配的元素值
 * @param cmp       元素值大小比较函数
 * @return          删除成功，则返回非0值，删除失败（不存在该
 *                  节点），则返回0。
 */
static int subtree_del(AVLTreeNode **node, AVLTreeValue value,
                       AVLTreeCompareFunc cmp)
{
    AVLTreeNode *root;
    AVLTreeNode *tmp;

    root = *node;

    /*
     * 未查找到要删除的节点
     */
    if (root == NULL) {
        return 0;

    /*
    * 待删除的节点在左子树中
    */
    } else if (cmp(value, root->data) < 0) {
        subtree_del(&root->left, value, cmp);

        /* 若右高左低，导致不平衡，则重新调整至平衡 */
        if (height(root->right) - height(root->left) == 2) {
            tmp = root->right;

            /* 对于node，相当于插入时的rr情况 */
            if (height(tmp->right) > height(tmp->left)) {
                rr_rotation(node);

                /* 对于node，相当于插入时的ll情况 */
            } else {
                rl_rotation(node);
            }
        }

    /*
     * 待删除节点在右子树中
     */
    } else if (cmp(value, root->data) > 0) {
        subtree_del(&root->right, value, cmp);

        /* 若左高右低，导致不平衡，则重新调整至平衡 */
        if (height(root->left) - height(root->right) == 2) {
            tmp = root->left;

            /* 对node，相当于ll情况 */
            if (height(tmp->left) > height(tmp->right)) {
                ll_rotation(node);

                /* 对于node，相当于lr情况 */
            } else {
                lr_rotation(node);
            }
        }

    /*
     * 当前节点即为要删除的节点
     */
    } else {
        /* 左右子树都非空 */
        if (root->left && root->right) {
            /*
             * 如果左子树的高度大于右子树，
             * 则（1）找出左子树中的最大值节点
             *   （2）赋值给当前node节点
             *   （3）删除该最大节点。
             * 这么做的好处是：删除该节点后，avl树仍是平衡的。
             */
            if (height(root->left) > height(root->right)) {
                AVLTreeNode *max;

                max = root->left;
                while (max && max->right) {
                    max = max->right;
                }
                root->data = max->data;
                subtree_del(&root->left, max->data, cmp);

                /*
                 * 如果左子树的高度不大于右子树，
                 * 则（1）找出右子树的最小值节点
                 *   （2）赋值给当前node节点
                 *   （3）删除该最小节点。
                 * 这么做的好处是：删除该节点后，avl树仍是平衡的。
                 */
            } else {
                AVLTreeNode *min;

                min = root->right;
                while (min && min->left) {
                    min = min->left;
                }
                root->data = min->data;
                subtree_del(&root->right, min->data, cmp);
            }

        /*
         * 左子树或右子树为空
         */
        } else {
            tmp = *node;

            *node = root->left ? root->left : root->right;
            free(tmp);
        }
    }

    /* 更新节点高度 */
    if (*node != NULL) {
        (*node)->height = MAX(height((*node)->left), height((*node)->right)) + 1;
    }
    return 1;
}


int avltree_del(AVLTree *avltree, AVLTreeValue value)
{
    return subtree_del(&avltree->root, value, avltree->cmp);
}

int avltree_depth(AVLTree *avltree)
{
    return height(avltree->root);
}

int avltree_is_empty(AVLTree *avltree)
{
    return avltree->root == NULL;
}

AVLTreeValue avltree_min(AVLTree *avltree)
{
    AVLTreeNode *node;

    node = avltree->root;

    /* 转左，找最小值 */
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }

    /* 树为空，无最小值 */
    if (node == NULL) {
        return AVLTREE_NULL;

        /* 树不空，存在最小值 */
    } else {
        return node->data;
    }
}

AVLTreeValue avltree_max(AVLTree *avltree)
{
    AVLTreeNode *node;

    node = avltree->root;

    /* 转右，找最大值 */
    while (node != NULL && node->right != NULL) {
        node = node->right;
    }

    /* 空树，无最大值 */
    if (node == NULL) {
        return AVLTREE_NULL;

        /* 树不空，存在最大值 */
    } else {
        return node->data;
    }
}
