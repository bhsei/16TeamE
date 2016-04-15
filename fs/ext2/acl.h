/*
  File: fs/ext2/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/posix_acl_xattr.h>

#define EXT2_ACL_VERSION	0x0001

/**
    ext2_acl_entry: ext2�ļ�ϵͳ��acl�ṹ�壬��ѭposix��׼����POSIX��׼��һ������ĳһ������ķ��ʿ��ƹ���
**  e_tag����ʾʵ���ʶ������ 6 �� e_tag ���ֱ��� ACL_USER_OBJ, ACL_USER, ACL_GROUP_OBJ, ACL_GROUP, ACL_MASK, ACL_OTHER
            �ֱ�����ļ������ļ������û����ļ��������ļ������飬�ļ����룬�����ˡ�
    e_perm: ��ʾȨ�ޡ�
    e_id: ��ʶ����ֻ��e_tagΪACL_USER_OBJ��ACL_GROUP_OBJʱ��Ч
**/
typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} ext2_acl_entry;

/**ext2�ļ�ϵͳ�ļ�̵Ľṹ�壬��posix��׼��������û����e_id�ֶ�**/
typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} ext2_acl_entry_short;

/**ext2��ͷ����������һ���汾��**/
typedef struct {
	__le32		a_version;
} ext2_acl_header;

/**������������acl��Ŀ����Ŀ���ext2��acl��С**/
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

/**��acl���ƽṹ��Ĵ�С����acl�����Ŀ**/
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

/**���������CONFIG_EXT2_FS_POSIX_ACL��������һЩ�꣬�������ú�ͺ���Ϊ��*/
#ifdef CONFIG_EXT2_FS_POSIX_ACL

/* acl.c */
extern struct posix_acl *ext2_get_acl(struct inode *inode, int type);
extern int ext2_set_acl(struct inode *inode, struct posix_acl *acl, int type);
extern int ext2_init_acl (struct inode *, struct inode *);

#else
#include <linux/sched.h>
#define ext2_get_acl	NULL
#define ext2_set_acl	NULL

/**��ʼ�������ڵ����ķ��ʿ����б�ACL��**/
static inline int ext2_init_acl (struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif

