/**
 * @file avl-tree.h
 *
 * @brief   AVL平衡二叉树
 *
 * AVL树是高度平衡的二叉搜索树，AVL树首先应满足二叉搜索树的性质：
 * (1).若它的左子树不为空，则左子树上所有结点的值均小于它的根结点的值；
 * (2).若它的右子树不为空，则右子树上所有结点的值均大于它的根结点的值；
 * (3).它的左、右子树也分别为二叉搜索树。
 *
 * AVL树的性质：
 * (1). 左子树和右子树的高度之差的绝对值不超过1；
 * (3). 树中的每个左子树和右子树都是AVL树；
 * (2).每个节点都有一个平衡因子(balance factor--bf),任一节点的平衡因子是-1,0,1之一。
 * (每个节点的平衡因子bf，等于右子树的高度减去左子树的高度 )
 */
#ifndef BULLET_AVLTREE_H
#define BULLET_AVLTREE_H

/**
 * AVL树
 */
typedef struct _AVLTree AVLTree;

/**
 * 节点数据类型
 */
typedef void *AVLTreeValue;

/**
 * 定义AVL树的空指针
 */
#define AVLTREE_NULL ((void *) 0)

/**
 * AVLTreeCompareFunc    回调函数，用于节点数据元素比较大小
 *
 * @param value1        元素1
 * @param value2        元素2
 * @return              若value1  < value2，则返回值小于0，
 *                      若value1 == value2，则返回值等于0，
 *                      若value1  > value2，则返回值大于0。
 */
typedef int (*AVLTreeCompareFunc)(AVLTreeValue value1, AVLTreeValue value2);

/**
 * avltree_new           创建AVL树
 *
 * @param cmp           节点元素比较函数
 * @return              创建AVL树成功，返回非0值，
 *                      失败，则返回0。
 */
extern AVLTree *avltree_new(AVLTreeCompareFunc cmp);

/**
 * avltree_free          销毁AVL树
 *
 * @param avltree        待销毁的AVL树
 */
extern void avltree_free(AVLTree *avltree);

/**
 * bstee_add            插入节点
 *
 * @param avltree        AVL树
 * @param value         待插入的元素值
 * @return              插入成功，则返回非0值，
 *                      失败（内存分配失败），则返回0。
 */
extern int avltree_add(AVLTree *avltree, AVLTreeValue value);

/**
 * avltree_find          查找节点
 *
 * @param avltree        AVL树
 * @param value         待查找的元素值
 * @return              若AVL树中存在节点值为value，则返回非0值，
 *                      若不存在，则返回0。
 */
extern int avltree_find(AVLTree *avltree, AVLTreeValue value);

/**
 * avltree_del           删除节点
 *
 * @param avltree        AVL树
 * @param value         待删除的节点元素值
 * @return              若删除成功，则返回非0值，
 *                      否则，AVL树中不存在该节点，返回0。
 */
extern int avltree_del(AVLTree *avltree, AVLTreeValue value);

/**
 * avltree_depth         AVL树的最大深度
 *
 * @param avltree        AVL树
 * @return              返回AVL树的深度，
 *                      树为空则返回0。
 */
extern int avltree_depth(AVLTree *avltree);

/**
 * avltree_is_empty      判断AVL树是否为空
 *
 * @param avltree        AVL树
 * @return              若AVL树不空，则返回0，
 *                      若AVL树为空，则返回非0值。
 */
extern int avltree_is_empty(AVLTree *avltree);

/**
 * avltree_min           查找AVL树最小值
 *
 * @param avltree        AVL树
 * @return              若查找最小值成功，则返回最小值，
 *                      若AVL树为空，则返回AVLTREE_NULL。
 */
extern AVLTreeValue avltree_min(AVLTree *avltree);

/**
 * avltree_max           查找AVL树最大值
 *
 * @param avltree        AVL树
 * @return              若查找最大值成功，则返回最大值，
 *                      若AVL树为空，则返回AVLTREE_NULL。
 */
extern AVLTreeValue avltree_max(AVLTree *avltree);

#endif /* BULLET_AVLTREE_H */
