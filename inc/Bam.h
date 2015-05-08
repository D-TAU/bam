#ifndef __bam_H__
#define __bam_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "bam"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.bam"
#endif

#define EDJ_FILE "edje/bam.edj"
#define GRP_MAIN "main"

#define BAM_LOG(fmt, arg...) dlog_print(DLOG_INFO, LOG_TAG, fmt, ##arg)
#define BAM_LOG_ERROR(fmt, arg...) dlog_print(DLOG_ERROR, LOG_TAG, fmt, ##arg)

#endif /* __bam_H__ */
