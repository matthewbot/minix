#ifndef __VFS_VACL_H__
#define __VFS_VACL_H__

struct vaclnode {
  uid_t an_uid;
  gid_t an_gid;
  mode_t an_mode;
};

EXTERN struct vacl {
  struct vaclnode a_nodes[NR_VACLNODES];
  struct vnode *a_node; /* vnode that has this acl, NULL if this vacl is unused */
} vacl[NR_VACLS];

#endif