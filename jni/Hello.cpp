#include "jni.h"

#include "./Hello.h"
#include <stdio.h>


JNIEXPORT void JNICALL Java_Hello_display
  (JNIEnv *env, jobject obj)
{
  jclass cls = env->GetObjectClass(obj);
  jfieldID fid = env->GetFieldID(cls, "a", "D");
  jdouble a = env->GetDoubleField(obj, fid);
  printf("Hello world zengping!a:%lf\n", a);
  return;
}

JNIEXPORT jdouble JNICALL Java_Hello_sumNative
  (JNIEnv *, jobject, jdouble a, jdouble b)
{
  return a + b;
}
