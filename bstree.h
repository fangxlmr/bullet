#ifndef BULLET_BSTREE_H
#define BULLET_BSTREE_H

#include <stdlib.h>
#include <stdio.h>
#define T BSTree_T

typedef struct T *T;

/* 新建二叉树根结点并初始化 */
extern T bst_new (void);

/* 判断二叉树是否为空 */
extern int bst_empty (T bst);

/* 求二叉树最大深度 */
extern int bt_depth (T bst);

/* 释放二叉树 */
extern void bst_free (T *bst);

/* 二叉树的前序遍历，标准输出结果 */
extern void bst_preorder (T bst);

/* 二叉树的中序遍历，标准输出结果*/
extern void bst_inorder (T bst);

/* 二叉树的后序遍历，标准输出结果*/
extern void bst_postorder (T bst);

/* 比较大小的回调函数 */

/*
 * int (*sort)(void *key1, void *key2)
 * 是用户定义的回调函数。
 * 当key1 > key2 时，返回1，
 * 相等返回0，
 * 小于则返回-1。
 */

/* 查找结点 */
extern int bst_key_search (T bst, void *key,
                           int (*sort)(void *key1, void *key2));

/* 插入结点 */
extern void bst_key_insert (T bst, void *key,
                            int (*sort)(void *key1, void *key2));

/* 删除结点 */
extern void bst_key_delete (T bst, void *key,
                            int (*sort)(void *key1, void *key2));

#undef T
#endif /* BULLET_BSTREE_H */