/*
 * Copyright 2003-2005 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 */

#include <jni.h>
#include "jvm.h"
#include "management.h"
#include "sun_management_ThreadImpl.h"

JNIEXPORT void JNICALL
Java_sun_management_ThreadImpl_setThreadContentionMonitoringEnabled0
  (JNIEnv *env, jclass cls, jboolean flag)
{
    jmm_interface->SetBoolAttribute(env, JMM_THREAD_CONTENTION_MONITORING, flag);
}

JNIEXPORT void JNICALL
Java_sun_management_ThreadImpl_setThreadCpuTimeEnabled0
  (JNIEnv *env, jclass cls, jboolean flag)
{
    jmm_interface->SetBoolAttribute(env, JMM_THREAD_CPU_TIME, flag);
}


JNIEXPORT void JNICALL
Java_sun_management_ThreadImpl_getThreadInfo0
  (JNIEnv *env, jclass cls, jlongArray ids, jint maxDepth,
   jobjectArray infoArray)
{
    jmm_interface->GetThreadInfo(env, ids, maxDepth, infoArray);
}

JNIEXPORT jobjectArray JNICALL
Java_sun_management_ThreadImpl_getThreads
  (JNIEnv *env, jclass cls)
{
    return JVM_GetAllThreads(env, cls);
}

JNIEXPORT jlong JNICALL
Java_sun_management_ThreadImpl_getThreadTotalCpuTime0
  (JNIEnv *env, jclass cls, jlong tid)
{
    return jmm_interface->GetThreadCpuTimeWithKind(env, tid, JNI_TRUE /* user+sys */);
}

JNIEXPORT jlong JNICALL
Java_sun_management_ThreadImpl_getThreadUserCpuTime0
  (JNIEnv *env, jclass cls, jlong tid)
{
    return jmm_interface->GetThreadCpuTimeWithKind(env, tid, JNI_FALSE /* user */);
}

JNIEXPORT jobjectArray JNICALL
Java_sun_management_ThreadImpl_findMonitorDeadlockedThreads0
  (JNIEnv *env, jclass cls)
{
    return jmm_interface->FindCircularBlockedThreads(env);
}

JNIEXPORT jobjectArray JNICALL
Java_sun_management_ThreadImpl_findDeadlockedThreads0
  (JNIEnv *env, jclass cls)
{
    return jmm_interface->FindDeadlocks(env, JNI_FALSE /* !object_monitors_only */);
}

JNIEXPORT void JNICALL
Java_sun_management_ThreadImpl_resetPeakThreadCount0
  (JNIEnv *env, jclass cls)
{
    jvalue unused;
    unused.i = 0;
    jmm_interface->ResetStatistic(env, unused, JMM_STAT_PEAK_THREAD_COUNT);
}

JNIEXPORT void JNICALL
Java_sun_management_ThreadImpl_resetContentionTimes0
  (JNIEnv *env, jobject dummy, jlong tid)
{
    jvalue value;
    value.j = tid;
    jmm_interface->ResetStatistic(env, value, JMM_STAT_THREAD_CONTENTION_TIME);
}

JNIEXPORT jobjectArray JNICALL
Java_sun_management_ThreadImpl_dumpThreads0
  (JNIEnv *env, jclass cls, jlongArray ids, jboolean lockedMonitors, jboolean lockedSynchronizers)
{
    return jmm_interface->DumpThreads(env, ids, lockedMonitors, lockedSynchronizers);
}
