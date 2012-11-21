#ifndef __VFS_REQUEST_H__
#define __VFS_REQUEST_H__

/* Low level request messages are built and sent by wrapper functions.
 * This file contains the request and response structures for accessing
 * those wrappers functions.
 */

#include <sys/types.h>
#include "const.h"

/* Structure for response that contains inode details */
typedef struct node_details {
  endpoint_t fs_e;
  ino_t inode_nr;
  mode_t fmode;
  off_t fsize;
  uid_t uid;
  gid_t gid;
  unsigned char hasacl;

  /* For char/block special files */
  dev_t dev;
} node_details_t;

/* Structure for a lookup response */
typedef struct lookup_res {
  endpoint_t fs_e;
  ino_t inode_nr;
  mode_t fmode;
  off_t fsize;
  uid_t uid;
  gid_t gid;
  /* For char/block special files */
  dev_t dev;

  /* Fields used for handling mount point and symbolic links */
  int char_processed;
  unsigned char symloop;

  /* Indicates the file has an ACL */
  unsigned char hasacl;
} lookup_res_t;

typedef struct acl_data {
  gid_t gids[NR_VACLNODES];
  uid_t uids[NR_VACLNODES];
  mode_t modes[NR_VACLNODES];
} acl_data_t;

#endif
