/**
 * @file bstree.h
 *
 * @brief   二叉排序树
 *
 * 二叉排序树或者是一棵空树，或者是具有下列性质的二叉树：
 * （1）若左子树不空，则左子树上所有结点的值均小于或等于它的根结点的值；
 * （2）若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值；
 * （3）左、右子树也分别为二叉排序树
 *
 * 使用BSTreeCompareFunc定义回调函数，用来判断元素大小。
 *
 * 使用bstree_new创建新的二叉排序树，
 * 使用bstree_free销毁已存在的二叉排序树。
 *
 * 使用bstree_add插入节点，使用bstree_fin查找已存在的树中是否存在节点，
 * 使用bstree_del删除节点。
 *
 * 使用bstree_depth获取二叉排序树的最大深度。
 *
 * 使用bstree_is_empty判断二叉排序树是否为空。
 *
 * 使用bstree_min查找当前二叉排序树中的最小值，
 * 使用bstree_max查找当前二叉排序树中的最大值。
 */

#ifndef BULLET_BSTREE_H
#define BULLET_BSTREE_H

/**
 * 二叉排序树
 */
typedef struct _BSTree BSTree;

/**
 * 节点数据类型
 */
typedef void *BSTreeValue;

/**
 * 定义二叉排序树空指针
 */
#define BSTREE_NULL ((void *) 0)

/**
 * BSTreeCompareFunc    回调函数，用于节点数据元素比较大小
 *
 * @param value1        元素1
 * @param value2        元素2
 * @return              若value1  < value2，则返回值小于0，
 *                      若value1 == value2，则返回值等于0，
 *                      若value1  > value2，则返回值大于0。
 */
typedef int (*BSTreeCompareFunc)(BSTreeValue value1, BSTreeValue value2);

/**
 * bstree_new           创建二叉排序树
 *
 * @param cmp           节点元素比较函数
 * @return              创建二叉排序树成功，返回非0值，
 *                      失败，则返回0。
 */
extern BSTree *bstree_new(BSTreeCompareFunc cmp);

/**
 * bstree_free          销毁二叉排序树
 *
 * @param bstree        待销毁的二叉排序树
 */
extern void bstree_free(BSTree *bstree);

/**
 * bstee_add            插入节点
 *
 * @param bstree        二叉排序树
 * @param value         待插入的元素值
 * @return              插入成功，则返回非0值，
 *                      失败（内存分配失败），则返回0。
 */
extern int bstree_add(BSTree *bstree, BSTreeValue value);

/**
 * bstree_find          查找节点
 *
 * @param bstree        二叉排序树
 * @param value         待查找的元素值
 * @return              若二叉排序树中存在节点值为value，则返回非0值，
 *                      若不存在，则返回0。
 */
extern int bstree_find(BSTree *bstree, BSTreeValue value);

/**
 * bstree_del           删除节点
 *
 * @param bstree        二叉排序树
 * @param value         待删除的节点元素值
 * @return              若删除成功，则返回非0值，
 *                      否则，二叉树中不存在该节点，返回0。
 */
extern int bstree_del(BSTree *bstree, BSTreeValue value);

/**
 * bstree_depth         二叉树的最大深度
 *
 * @param bstree        二叉排序树
 * @return              返回二叉排序树的深度，
 *                      树为空则返回0。
 */
extern int bstree_depth(BSTree *bstree);

/**
 * bstree_is_empty      判断二叉树是否为空
 *
 * @param bstree        二叉排序树
 * @return              若二叉排序树不空，则返回0，
 *                      若二叉排序树为空，则返回非0值。
 */
extern int bstree_is_empty(BSTree *bstree);

/**
 * bstree_min           查找二叉排序树最小值
 *
 * @param bstree        二叉排序树
 * @return              若查找最小值成功，则返回最小值，
 *                      若二叉排序树为空，则返回BSTREE_NULL。
 */
extern BSTreeValue bstree_min(BSTree *bstree);

/**
 * bstree_max           查找二叉排序树最大值
 *
 * @param bstree        二叉排序树
 * @return              若查找最大值成功，则返回最大值，
 *                      若二叉排序树为空，则返回BSTREE_NULL。
 */
extern BSTreeValue bstree_max(BSTree *bstree);

#endif /* BULLET_BSTREE_H */