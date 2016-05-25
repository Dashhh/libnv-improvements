/*
 * TODO: add legal note
 * TODO: what if cookiep is bad?
 */

#ifndef _CNV_H_
#define _CNV_H_

//
// TODO: add includes 
//

#ifndef _NVLIST_T_DECLARED
#define _NVLIST_T_DECLARED
struct nvlist;

typedef struct nvlist nvlist_t;
#endif

__BEGIN_DECLS

/*
 * The nvlist_add functions add the given name/value pair and return the cookie for it.
 * If a pointer is provided, nvlist_add will internally allocate memory for the
 * given data (in other words it won't consume provided buffer).
 */

void *cnvlist_add_null(nvlist_t *nvl, const char *name);
void *cnvlist_add_bool(nvlist_t *nvl, const char *name, bool value);
void *cnvlist_add_number(nvlist_t *nvl, const char *name, uint64_t value);
void *cnvlist_add_string(nvlist_t *nvl, const char *name, const char *value);
void *cnvlist_add_stringf(nvlist_t *nvl, const char *name, const char *valuefmt, ...) __printflike(3, 4);
#if !defined(_KERNEL) || defined(_VA_LIST_DECLARED)
void *cnvlist_add_stringv(nvlist_t *nvl, const char *name, const char *valuefmt, va_list valueap) __printflike(3, 0);
#endif
void *cnvlist_add_nvlist(nvlist_t *nvl, const char *name, const nvlist_t *value);
void *cnvlist_add_binary(nvlist_t *nvl, const char *name, const void *value, size_t size);
void *cnvlist_add_bool_array(nvlist_t *nvl, const char *name, const bool *value, size_t nitems);
void *cnvlist_add_number_array(nvlist_t *nvl, const char *name, const uint64_t *value, size_t nitems);
void *cnvlist_add_string_array(nvlist_t *nvl, const char *name, const char * const *value, size_t nitems);
void *cnvlist_add_nvlist_array(nvlist_t *nvl, const char *name, const nvlist_t * const *value, size_t nitems);
#ifndef _KERNEL
void *cnvlist_add_descriptor(nvlist_t *nvl, const char *name, int value);
void *cnvlist_add_descriptor_array(nvlist_t *nvl, const char *name, const int *value, size_t nitems);
#endif

/*
 * The cnvlist_move functions add the given name/value pair and returns cookie associated with it.
 * The functions consumes provided buffer.
 */

void *cnvlist_move_string(nvlist_t *nvl, const char *name, char *value);
void *cnvlist_move_nvlist(nvlist_t *nvl, const char *name, nvlist_t *value);
void *cnvlist_move_binary(nvlist_t *nvl, const char *name, void *value, size_t size);
void *cnvlist_move_bool_array(nvlist_t *nvl, const char *name, bool *value, size_t nitems);
void *cnvlist_move_string_array(nvlist_t *nvl, const char *name, char **value, size_t nitems);
void *cnvlist_move_nvlist_array(nvlist_t *nvl, const char *name, nvlist_t **value, size_t nitems);
void *cnvlist_move_number_array(nvlist_t *nvl, const char *name, uint64_t *value, size_t nitems);
#ifndef _KERNEL
void *cnvlist_move_descriptor(nvlist_t *nvl, const char *name, int value);
void *cnvlist_move_descriptor_array(nvlist_t *nvl, const char *name, int *value, size_t nitems);
#endif

/*
 * The cnvlist_get functions returns value associated with the given cookie.
 * If it returns a pointer, the pointer represents internal buffer and should
 * not be freed by the caller.
 * TODO: justify?
 */

bool			 cnvlist_get_bool(const nvlist_t *nvl, void **cookiep);
uint64_t		 cnvlist_get_number(const nvlist_t *nvl, void **cookiep);
void **cookiep		*cnvlist_get_string(const nvlist_t *nvl, void **cookiep);
const nvlist_t		*cnvlist_get_nvlist(const nvlist_t *nvl, void **cookiep);
const void		*cnvlist_get_binary(const nvlist_t *nvl, void **cookiep, size_t *sizep);
const bool		*cnvlist_get_bool_array(const nvlist_t *nvl, void **cookiep, size_t *nitemsp);
const uint64_t		*cnvlist_get_number_array(const nvlist_t *nvl, void **cookiep, size_t *nitemsp);
void **cookiep * const	*cnvlist_get_string_array(const nvlist_t *nvl, void **cookiep, size_t *nitemsp);
const nvlist_t * const	*cnvlist_get_nvlist_array(const nvlist_t *nvl, void **cookiep, size_t *nitemsp);
#ifndef _KERNEL
int			 cnvlist_get_descriptor(const nvlist_t *nvl, void **cookiep);
const int		*cnvlist_get_descriptor_array(const nvlist_t *nvl, void **cookiep, size_t *nitemsp);
#endif

/*
 * The cnvlist_take functions returns value associated with the given cookie and
 * remove the given entry from the nvlist.
 * The caller is responsible for freeing received data.
 */

bool		  cnvlist_take_bool(nvlist_t *nvl, void **cookiep);
uint64_t	  cnvlist_take_number(nvlist_t *nvl, void **cookiep);
char		 *cnvlist_take_string(nvlist_t *nvl, void **cookiep);
nvlist_t	 *cnvlist_take_nvlist(nvlist_t *nvl, void **cookiep);
void		 *cnvlist_take_binary(nvlist_t *nvl, void **cookiep, size_t *sizep);
bool		 *cnvlist_take_bool_array(nvlist_t *nvl, void **cookiep, size_t *nitemsp);
uint64_t	 *cnvlist_take_number_array(nvlist_t *nvl, void **cookiep, size_t *nitemsp);
char		**cnvlist_take_string_array(nvlist_t *nvl, void **cookiep, size_t *nitemsp);
nvlist_t	**cnvlist_take_nvlist_array(nvlist_t *nvl, void **cookiep, size_t *nitemsp);
#ifndef _KERNEL
int		 cnvlist_take_descriptor(nvlist_t *nvl, void **cookiep);
int		 *cnvlist_take_descriptor_array(nvlist_t *nvl, void **cookiep, size_t *nitemsp);
#endif

/*
 * The cnvlist_free functions removes the given name/value pair from the nvlist based on cookie
 * and frees memory associated with it.
 */

void cnvlist_free(nvlist_t *nvl, void **cookiep);
void cnvlist_free_type(nvlist_t *nvl, void **cookiep, int type);

void cnvlist_free_null(nvlist_t *nvl, void **cookiep);
void cnvlist_free_bool(nvlist_t *nvl, void **cookiep);
void cnvlist_free_number(nvlist_t *nvl, void **cookiep);
void cnvlist_free_string(nvlist_t *nvl, void **cookiep);
void cnvlist_free_nvlist(nvlist_t *nvl, void **cookiep);
void cnvlist_free_binary(nvlist_t *nvl, void **cookiep);
void cnvlist_free_bool_array(nvlist_t *nvl, void **cookiep);
void cnvlist_free_number_array(nvlist_t *nvl, void **cookiep);
void cnvlist_free_string_array(nvlist_t *nvl, void **cookiep);
void cnvlist_free_nvlist_array(nvlist_t *nvl, void **cookiep);
void cnvlist_free_binary_array(nvlist_t *nvl, void **cookiep);
#ifndef _KERNEL
void cnvlist_free_descriptor(nvlist_t *nvl, void **cookiep);
void cnvlist_free_descriptor_array(nvlist_t *nvl, void **cookiep);
#endif

__END_DECLS

#endif	/* !_CNV_H_ */
