/*
 * 二叉排序树(bstree)的代码实现
 */

#include <stdlib.h>
#include "bstree.h"
/*
 * 判断a, b大小，返回较大值。
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/*
 * 节点结构
 */
typedef struct _BSTreeEntry BSTreeEntry;

typedef struct _BSTreeEntry {
    BSTreeValue data;
    BSTreeEntry *left;
    BSTreeEntry *right;
};

/*
 * 二叉排序树
 */
struct _BSTree {
    BSTreeEntry *root;           /* 根节点 */
    BSTreeCompareFunc cmp;  /* 节点大小比较函数 */
};

BSTree *bstree_new(BSTreeCompareFunc cmp)
{
    BSTree *bstree;

    bstree = (BSTree *) malloc(sizeof(BSTree));

    if (!bstree) {
        return BSTREE_NULL;
    }

    bstree->root = NULL;
    bstree->cmp  = cmp;

    return bstree;
}

/**
 * subtree_free     销毁子树
 *
 * @param root      子树根节点
 */
static void subtree_free(BSTreeEntry *root)
{
    if (!root) {
        return;
    }
    /*
     * 分别销毁左右子树
     */
    subtree_free(root->left);
    subtree_free(root->right);
    /*
     * 释放当前节点
     */
    free(root);
}

void bstree_free(BSTree *bstree)
{
    subtree_free(bstree->root);
}

int bstree_is_empty(BSTree *bstree)
{
    if (bstree->root == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * subtree_depth    求子树的高度
 *
 * @param root      子树根节点
 * @return          若子树为空，则饭会0，
 *                  若子树不空，返回子树的高度。
 */
static int subtree_depth(BSTreeEntry *root)
{
    if (!root)
        return 0;
    /*
     * 当前子树的高度为左右子树的最大值 + 1
     */
    return MAX(subtree_depth(root->left), subtree_depth(root->right)) + 1;
}

int bstree_depth(BSTree *bstree)
{
    return subtree_depth(bstree->root);
}

/**
 * subtree_find     查找子树中是否存在节点值等于value
 *
 * @param root      子树根节点
 * @param value     待查找的元素
 * @param cmp       节点元素比较函数
 * @return          若子树中含有元素value，则返回非0值，
 *                  否则返回0。
 */
static int subtree_find(BSTreeEntry *root,
                        BSTreeValue value,
                        BSTreeCompareFunc cmp)
{
    /* 已经遍历完毕子树的所有节点，未匹配，返回0 */
    if (!root) {
        return 0;
    }

    /* 当前节点即匹配 */
    if (cmp(value, root->data) == 0) {
        return 1;

    /* 查找左子树 */
    } else if (cmp(value, root->data) < 0) {
        return subtree_find(root->left, value, cmp);

    /* 查找有子树 */
    } else {
        return subtree_find(root->right, value, cmp);
    }
}

int bstree_find(BSTree *bstree, BSTreeValue value)
{
    return subtree_find(bstree->root, value, bstree->cmp);
}

/**
 * subtree_add      向子树中添加元素value
 *
 * @param root      子树根节点的二级指针
 * @param value     带添加的元素
 * @param cmp       节点元素比较大小函数
 * @return          添加成功，则返回非0值，
 *                  添加失败（内存分配失败）则返回0。
 */
static int subtree_add(BSTreeEntry **root,
                       BSTreeValue value,
                       BSTreeCompareFunc cmp)
{
    BSTreeEntry *new_entry;

    /*
     * 没有匹配的节点，新建节点，并插入二叉排序树
     */
    if (!*root) {
        new_entry = (BSTreeEntry *) malloc(sizeof(BSTreeEntry));

        if (!new_entry) {   /* 内存分配失败 */
            return 0;
        }

        /* 新节点 */
        new_entry->data  = value;
        new_entry->left  = NULL;
        new_entry->right = NULL;

        *root = new_entry;  /* 插入 */
        return 1;
    }

    if (cmp(value, (*root)->data) == 0) {
        return 0;     /* 忽略重复值 */

    /* 查找左子树 */
    } else if (cmp(value, (*root)->data) < 0) {
        subtree_add(&(*root)->left, value, cmp);

    /* 查找右子树 */
    } else {
        subtree_add(&(*root)->right, value, cmp);
    }
}

int bstree_add(BSTree *bstree, BSTreeValue value)
{
    return subtree_add(&bstree->root, value, bstree->cmp);
}



/**
 * delete_node      删除二叉排序树中的单个节点
 *
 * @param node      待删除节点的二级指针
 *
 * @note            需要处理三种不同的节点位置情况
 *                  [1]  左孩子为空
 *                  [2]  右孩子为空
 *                  [3]  左右孩子都不空
 */
static void delete_node(BSTreeEntry **node) {
    BSTreeEntry *p, *q;

    /* [1] */
    if (!(*node)->left) {
        p = *node;
        *node = p->right;
        free(p);

     /* [2] */
    } else if (!(*node)->right) {
        p = *node;
        *node = p->left;
        free(p);

    /* [3] */
    } else {
        p = *node;  /* 保存当前节点指针 */

        /* 转左孩子，找到待删除节点的直接前驱 */
        q = p->left;
        while (q->right) {
            p = q;
            q = q->right;
        }
        /*
         * 将直接前驱的值复制到带删除节点，
         * 就相当于删除了待删除节点。
         */
        (*node)->data = q->data;

        /*
         * 处理直接前驱的子树。
         *
         * 如果p与*node指向相同，则重接p的左子树。
         * 此种情况为，待删除节点的左孩子没有右子树，
         * 直接前驱就为左孩子本身。
         * 则将直接前驱的左孩子重接到待删除节点的左孩子处。
         */
        if (p == *node) {
            p->left = q->left;
            free(q);

        /*
         * 如果p与*node的指向不同，则重接p的右子树。
         * 此种情况为，待删除节点的左孩子存在右子树，
         * 直接前驱不是左孩子。
         * 则将直接前驱的左孩子重接到直接前驱父节点的右孩子处。
         */
        } else {
            p->right = q->left;
            free(q);
        }
    }
}
/**
 * subtree_del      删除子树中元素值等于value的节点
 *
 * @param root      子树根节点的二级指针
 * @param value     目标元素值
 * @param cmp       节点元素比较大小函数
 * @return          删除成功，则返回非0值，
 *                  删除失败，则返回0。
 */
static int subtree_del(BSTreeEntry **root,
                        BSTreeValue value,
                        BSTreeCompareFunc cmp)
{
    /*
     * 不存在值为value的节点
     */
    if (!*root) {
        return 0;
    }

    if (cmp(value, (*root)->data) == 0) {
        /*
         * 节点匹配，删除之
         */
        delete_node(root);
        return 1;
        /*
         * 查找左子树
         */
    } else if (cmp(value, (*root)->data) < 0) {
        subtree_del(&(*root)->left, value, cmp);
        /*
         * 查找右子树
         */
    } else {
        subtree_del(&(*root)->right, value, cmp);
    }
}

int bstree_del(BSTree *bstree, void *value)
{
    return subtree_del(&bstree->root, value, bstree->cmp);
}
