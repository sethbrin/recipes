#include "ClassAccess.h"

#include <jni.h>

#include <string>
#include <iostream>

JNIEXPORT void JNICALL Java_ClassAccess_nativeMethod
  (JNIEnv *env, jobject obj)
{
  jclass cls = env->GetObjectClass(obj);
  jfieldID fid = env->GetFieldID(cls, "str", "Ljava/lang/String;");
  jstring jstr = (jstring)env->GetObjectField(obj, fid);
  const char *str = env->GetStringUTFChars(jstr, false);

  if (std::string(str) == "abcde") {
    std::cout << "access field succeeded" << std::endl;
  }
  jdouble i = 246.8;
  fid = env->GetFieldID(cls, "number", "D");
  env->SetDoubleField(obj, fid, i);

  jmethodID mid = env->GetMethodID(cls, "javaMethod", "()V");

  env->CallVoidMethod(obj, mid);

}
