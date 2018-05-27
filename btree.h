#ifndef BULLET_BTREE_H
#define BULLET_BTREE_H

#include <stdlib.h>
#include <stdio.h>
#define T BTree_T

typedef struct T *T;

/* 新建二叉树根结点并初始化 */
extern T bt_new (void);

/* 判断二叉树是否为空 */
extern int bt_empty (T root);

/* 求二叉树最大深度 */
extern int bt_depth (T root);

/* 释放二叉树 */
extern void bt_free (T *root);

/* 二叉树的前序遍历，标准输出结果 */
extern void bt_preorder (T root);

/* 二叉树的中序遍历，标准输出结果*/
extern void bt_inorder (T root);

/* 二叉树的后序遍历，标准输出结果*/
extern void bt_postorder (T root);

#undef T
#endif /* BULLET_BTREE_H */
