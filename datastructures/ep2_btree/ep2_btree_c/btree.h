#ifdef __cplusplus
extern "C" {
#endif

typedef int elem;
typedef struct tree_s *btree;

/* Create a tree
 *
 * Returns
 * =======
 *  NULL - please don't try to dereference this
 *         it only exists to conform with the usual
 *         function signature of other data structures
 */
btree btree_create();

/* Destroy a tree */
void btree_destroy(btree t);

/* Insert a value into the tree
 *
 * Returns
 * =======
 *  0 - no error
 *  1 - error
 */
int btree_insert(btree *t, const elem val);

/* Find a value in the tree
 *
 * Returns
 * =======
 *  0 - value not found in tree
 *  1 - value found
 */
int btree_find(btree t, const elem val);

#ifdef __cplusplus
}
#endif
