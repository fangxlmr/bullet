#include "btree.h"


/** max of two variables */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* Static functions declaration */
/**
 * @brief 从给定数组创建二叉树
 * @param root 二叉树的结点地址
 * @param array 给定数组
 * @param len 数组长度
 * @param index 对应结点的数组下标
 *
 * 采用递归的方法创建，index结点创建完毕后，对应的left与right
 * 结点的数组下标为 2 * index + 1 与 2 * index + 2.
 */
static void create_tree (pBTNode *root, BTElemType *array, int len, int index);

/**
 * @brief 将外部传入的字符串分解，转化为字符串指针数组
 * @param s 字符串
 * @return 返回一个字符串指针数组
 *
 * 形如 s = "[1, 2, 5, 22, null, 0, 79]"的字符串
 * 分解后变为 s1 = ["1", "2", "5", "22", "null", "0", "79"]
 * 然后返回数组 s1
 * 若字符串 s 为空，则返回 null
 */
static char *str_split (char s);




/* External functions*/
/**
 * @brief 从给定数组创建二叉树
 * @return 完成则返回数组地址，否则返回null
 *
 * 与static void create_tree联合完成从数组创建二叉树的任务。
 */
pBTNode bt_created_with_array (BTElemType *array, size_t len) {
    pBTNode root = (pBTNode) calloc(1, sizeof(BTNode));
    create_tree(&root, array, len, 0);
    return root;
}



/**
 * bt_creat - create and initialize a BT.
 *
 * Return a pBTNode if success, or return false.
 */
pBTNode bt_create (void) {
    pBTNode p = (pBTNode) calloc(1, sizeof(BTNode));
    if (!p)
        return NULL;
    return p;
}


/**
 * bt_isempty - check btree is empty or not
 *
 * If tree is empty, return true.
 * Or return false.
 */
bool bt_empty (pBTNode root) {
    if (!root)
        return true;
    return false;
}


/**
 * bst_depth - find the depth of btree
 *
 * Return depth of the btree.
 * Return 0 if null.
 */
/* TODO it iteratively */
size_t bt_depth (pBTNode root) {
    if (!root)
        return 0;
    return MAX(bt_depth(root->left), bt_depth(root->right)) + 1;
}


/**
 * bt_destroy - destroy a btree.
 */
void bt_destroy (pBTNode *root) {
    pBTNode *p = root;
    if (!*root) {
        return;
    }
    bt_destroy(&(*root)->left);
    (*root)->left = NULL;
    bt_destroy(&(*root)->right);
    (*root)->right = NULL;
    free(*p);
    *p = NULL;
}


/**
 * bt_preoder - preorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_preorder (pBTNode root) {
    if (!root) {
        return;
    }
    /* TODO: Define a dynamic array at the beginning
     * TODO: save values in a dynamic array: darray_append()
     */
    printf("val = %d", root->b);
    bt_preorder(root->left);
    bt_preorder(root->right);

}

/**
 * bt_inoder - inorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_inorder (pBTNode root) {
    if (!root) {
        return;
    }
    /* TODO: Define a dynamic array at the beginning
     * TODO: save values in a dynamic array: darray_append()
     * */
    bt_inorder(root->left);
    printf("%d, ", root->b);
    bt_inorder(root->right);
}

/**
 * bt_postoder - postorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_postorder (pBTNode root) {
    if (!root) {
        return;
    }
    /* TODO: Define a dynamic array at the beginning
     * TODO: save values in a dynamic array: darray_append()
     * */
    bt_postorder(root->left);
    bt_postorder(root->right);
    printf("%d\n", root->b);
}


/* Static functions */
/**
 * @brief 从给定数组创建二叉树
 * @param root 二叉树的结点地址
 * @param array 给定数组
 * @param len 数组长度
 * @param index 对应结点的数组下标
 *
 * 采用递归的方法创建，index结点创建完毕后，对应的left与right
 * 结点的数组下标为 2 * index + 1 与 2 * index + 2.
 */
static void create_tree (pBTNode *root, BTElemType *array, int len, int index) {
    if (index >= len) {
        return;
    }
    pBTNode new = (pBTNode) malloc(sizeof(BTNode));
    new->b = array[index];
    new->left = new->right = NULL;
    *root = new;
    /* 创建子节点 */
    create_tree(&(*root)->left, array, len, 2 * index + 1);
    create_tree(&(*root)->right, array, len, 2 * index + 2);
}


/**
 * @brief 将外部传入的字符串分解，转化为字符串指针数组
 * @param s 字符串
 * @return 返回一个字符串指针数组
 */
static char *str_split (char s) {
    size_t s_len = strlen(&s);
    if (!s_len) {
        return NULL;
    }
    size_t t_len = s_len - 2;   /* 去掉开头和结尾的 2 个中括号的长度 */
    char *t = (char *) calloc(t_len, sizeof(char));
    strncpy(t, &s + 1, t_len);
    strs
}