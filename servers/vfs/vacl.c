/* This file contains the routines related to vacls.
 * The entry points are:
 *
 * init_vacls - Initializes the pool of vacls
 * get_free_vacl - Returns a pointer to an unused vacl
 * add_vacl_to_vnode - Adds a vacl to a vnode
 * remove_vacl - Removes a vacl entry from its vnode
 * check_vacls - Finds all vacls matching a uid and gid and ors together their permissions
 * find_vacl - Finds a vacl matching either a uid or a gid 
 */

#include "fs.h"
#include "vacl.h"
#include "vnode.h"
#include <assert.h>
#include <string.h>

struct vacl vacl[NR_VACLS];

PUBLIC void init_vacls(void)
{
  struct vacl *va;

  for (va = &vacl[0]; va < &vacl[NR_VACLS]; ++va) {
	va->a_node = NULL;
  }
}

PUBLIC struct vacl *get_free_vacl()
{
  struct vacl *ap;

  for (ap = &vacl[0]; ap < &vacl[NR_VACLS]; ++ap) {
	if (ap->a_node == NULL) {
		memset(&ap->a_nodes, '\0', NR_VACLNODES*sizeof(struct vaclnode));
		return(ap);
	}
  }

  return NULL;
}

PUBLIC mode_t check_vacls(struct vacl *ap, uid_t uid, gid_t gid)
{
  struct vaclnode *np;
  mode_t mode = 0;

  for (np = &ap->a_nodes[0]; np < &ap->a_nodes[NR_VACLNODES]; ++np) {
	if (np->an_uid == uid || np->an_gid == gid)
		mode |= np->an_mode;
  }

  return(mode);
}

PUBLIC struct vaclnode *find_vacl_node(struct vacl *ap, uid_t uid, gid_t gid)
{
  struct vaclnode *np;
  for (np = &ap->a_nodes[0]; np < &ap->a_nodes[NR_VACLNODES]; ++np) {
	if (np->an_uid == uid || np->an_gid == gid)
		return(np);
  }
 
  return(NULL);
}