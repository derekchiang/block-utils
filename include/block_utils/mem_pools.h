#pragma once

#include "stddef.h"
#include "stdio.h"

#include "apr_general.h"
#include "apr_strings.h"

extern void bu_with_pool(bu_normal_b);

extern apr_pool_t *bu_current_pool(void);

extern void *bu_alloc(size_t size);

#define bu_format(str, args...) \
    apr_psprintf(bu_current_pool(), str, ## args)

#define bu_log(str, args...) \
    puts(bu_format(str, ## args))

