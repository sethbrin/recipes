#include "jni.h"

#include "./Hello.h"
#include <stdio.h>


JNIEXPORT void JNICALL Java_Hello_display
  (JNIEnv *, jobject)
{
  printf("Hello world zengping!\n");
  return;
}

JNIEXPORT jdouble JNICALL Java_Hello_sumNative
  (JNIEnv *, jobject, jdouble a, jdouble b)
{
  return a + b;
}
