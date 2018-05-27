#include "btree.h"

#define T BTree_T
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* 结点的结构 */
struct T {
    void *x;
    struct T *left, *right;
};


/* 新建二叉树根结点并初始化 */
T bt_new (void) {
    T t = (T) malloc(sizeof(struct T));
    t->x = NULL;
    t->left = t->right = NULL;
    return t;
}


/* 判断二叉树是否为空 */
int bt_empty (T root) {
    if (!root)
        return 1;
    return 0;
}


/* 求二叉树最大深度 */
int bt_depth (T root) {
    if (!root)
        return 0;
    return MAX(bt_depth(root->left), bt_depth(root->right)) + 1;
}


/* 释放二叉树 */
void bt_free (T *root) {
    if (!*root) {
        return;
    }

    bt_free(&(*root)->left);
    bt_free(&(*root)->right);
    free(*root);
    *root = NULL;
}


/*
 * TODO: 二叉树的前序、中序、后续遍历
 * TODO: 用自定义栈去实现
 */
/* 二叉树的前序遍历，标准输出结果 */
void bt_preorder (T root) {
    if (!root) {
        return;
    }

    printf("%d,", root->b);
    bt_preorder(root->left);
    bt_preorder(root->right);

}

/* 二叉树的中序遍历，标准输出结果 */
void bt_inorder (T root) {
    if (!root) {
        return;
    }
    bt_inorder(root->left);
    printf("%d,", root->b);
    bt_inorder(root->right);
}

/* 二叉树的后序遍历，标准输出结果 */
void bt_postorder (T root) {
    if (!root) {
        return;
    }
    bt_postorder(root->left);
    bt_postorder(root->right);
    printf("%d,", root->b);
}