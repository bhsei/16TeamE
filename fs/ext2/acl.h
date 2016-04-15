/*
  File: fs/ext2/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/posix_acl_xattr.h>

#define EXT2_ACL_VERSION	0x0001

/**
    ext2_acl_entry: ext2文件系统的acl结构体，遵循posix标准，和POSIX标准的一样代表某一个具体的访问控制规则
**  e_tag：表示实体标识，共有 6 种 e_tag ，分别是 ACL_USER_OBJ, ACL_USER, ACL_GROUP_OBJ, ACL_GROUP, ACL_MASK, ACL_OTHER
            分别代表文件主，文件其他用户，文件组主，文件其他组，文件掩码，其他人。
    e_perm: 表示权限。
    e_id: 标识符，只有e_tag为ACL_USER_OBJ和ACL_GROUP_OBJ时有效
**/
typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} ext2_acl_entry;

/**ext2文件系统的简短的结构体，和posix标准的区别是没有了e_id字段**/
typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} ext2_acl_entry_short;

/**ext2的头部，仅仅有一个版本号**/
typedef struct {
	__le32		a_version;
} ext2_acl_header;

/**内联函数，从acl项目的数目获得ext2的acl大小**/
static inline size_t ext2_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(ext2_acl_header) +
		       count * sizeof(ext2_acl_entry_short);
	} else {
		return sizeof(ext2_acl_header) +
		       4 * sizeof(ext2_acl_entry_short) +
		       (count - 4) * sizeof(ext2_acl_entry);
	}
}

/**从acl控制结构体的大小返回acl项的数目**/
static inline int ext2_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ext2_acl_header);
	s = size - 4 * sizeof(ext2_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(ext2_acl_entry_short))
			return -1;
		return size / sizeof(ext2_acl_entry_short);
	} else {
		if (s % sizeof(ext2_acl_entry))
			return -1;
		return s / sizeof(ext2_acl_entry) + 4;
	}
}

/**如果配置了CONFIG_EXT2_FS_POSIX_ACL，就设置一些宏，否则设置宏和函数为空*/
#ifdef CONFIG_EXT2_FS_POSIX_ACL

/* acl.c */
extern struct posix_acl *ext2_get_acl(struct inode *inode, int type);
extern int ext2_set_acl(struct inode *inode, struct posix_acl *acl, int type);
extern int ext2_init_acl (struct inode *, struct inode *);

#else
#include <linux/sched.h>
#define ext2_get_acl	NULL
#define ext2_set_acl	NULL

/**初始化索引节点对象的访问控制列表（ACL）**/
static inline int ext2_init_acl (struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif

