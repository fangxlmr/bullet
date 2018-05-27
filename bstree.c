#include <assert.h>
#include "bstree.h"

#define T BSTree_T
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* 结点的结构 */
typedef struct BSTNode {
    void *x;
    struct BSTNode *left, *right;
}*BSTNode;

struct T {
    BSTNode root;
};


static void delete (BSTNode node);

/* 新建二叉树根结点并初始化 */
T bst_new (void) {
    T t = (T) malloc(sizeof(struct T));
    t->root = NULL;
    return t;
}


/* 判断二叉树是否为空 */
int bst_empty (T root) {
    if (!root->root)
        return 1;
    return 0;
}

/* 求二叉树最大深度 */
static int depth (BSTNode root) {
    if (!root)
        return 0;
    return MAX(depth(root->left), depth(root->right)) + 1;
}
int bst_depth (T bst) {
    return depth(bst->root);
}


/* 释放二叉树 */
static void destroy (BSTNode *root) {
    if (!*root) {
        return;
    }
    destroy(&(*root)->left);
    destroy(&(*root)->right);
    free(*root);
    *root = NULL;
}
void bst_free (T *bst) {
    assert(bst && *bst);
    destroy(&(*bst)->root);
    *bst = NULL;
}


static int search (BSTNode root, void *key,
                   int (*sort)(void *key1, void *key2)) {
    if (sort(key, root->x) == 0) {
        return 1;
    }
    if (sort(key, root->x) < 0) {
        return search(root->left,  key, sort);
    } else {
        return search(root->right, key, sort);
    }
}

/* 查找结点 */
int bst_key_search (T bst, void *key,
                    int (*sort)(void *key1, void *key2)) {
    assert(bst && bst->root);

    return search(bst->root, key, sort);
}


static void insert (BSTNode *root, void *key,
                    int (*sort)(void *key1, void *key2)) {
    if (!*root) {
        BSTNode p = (BSTNode) malloc(sizeof(struct BSTNode));
        p->x = key;
        p->left = p->right = NULL;
        *root = p;
        return;
    }
    else if (sort(key, (*root)->x) == 0) {
        return;     /* 忽略重复值 */
    }
    else if (sort(key, (*root)->x)) {
        insert(&(*root)->left, key, sort);
    }
    else {
        insert(&(*root)->right, key, sort);
    }
}

/* 插入结点 */
void bst_key_insert (T bst, void *key,
                     int (*sort)(void *key1, void *key2)) {
    assert(bst);
    insert(&bst->root, key, sort);
}



/**
 * 删除结点，处理待删除结点的三种情况
 * [1]  做孩子为空
 * [2]  右孩子为空
 * [3]  左右孩子都不空
 */
static void node_delete (BSTNode *node) {
    BSTNode p, q;
    if (!(*node)->left) {   /* [1] */
        p = *node;
        *node = (*node)->right;
        free(p);
    } else if (!(*node)->right) {   /* [2] */
        p = *node;
        *node = (*node)->left;
        free(p);
    } else {                /* [3] */
        p = *node;
        /*
         * 当待删除结点的直接前驱也有左孩子
         */
        q = (*node)->left;
        while (q->right) {
            p = q;
            q = q->right;
        }
        (*node)->x = q->x;
        if (p == *node) {
            p->left = q->left;
            free(q);
        } else {
            p->right = q->left;
            free(q);
        }
    }
}
/* 删除结点 */
static void key_delete (BSTNode *root, void *key,
                        int (*sort)(void *key1, void *key2)) {
    if (sort(key, (*root)->x) == 0) {
        node_delete(root);
        return;
    }
    else if (sort(key, (*root)->x) < 0) {
        key_delete(&(*root)->left, key, sort);
    }
    else {
        key_delete(&(*root)->right, key, sort);
    }
}
void bst_key_delete (T bst, void *key,
                     int (*sort)(void *key1, void *key2)){
    assert(bst);

    key_delete(&bst->root, key, sort);
}


/*
 * TODO: 二叉树的前序、中序、后续遍历
 * TODO: 用自定义栈去实现
 */
/* 二叉树的前序遍历，标准输出结果 */
void bst_preorder (T root) {
    assert(root);

    printf("%d,", root->b);
    bst_preorder(root->left);
    bst_preorder(root->right);

}

/* 二叉树的中序遍历，标准输出结果 */
void bst_inorder (T root) {
    assert(root);

    bst_inorder(root->left);
    printf("%d,", root->b);
    bst_inorder(root->right);
}

/* 二叉树的后序遍历，标准输出结果 */
void bst_postorder (T root) {
    assert(root);

    bst_postorder(root->left);
    bst_postorder(root->right);
    printf("%d,", root->b);
}






