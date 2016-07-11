#include "TestJNIArray.h"

#include <time.h>
#include <iostream>
#include <string>

class Timer{
private:
  clock_t time;
public:
  Timer(){
    time = clock();
  }

  clock_t getElapsedTime(){
    return clock() - time;
  }

  clock_t getElapsedTimeAndRestart(){
    clock_t tmp = time;
    time = clock();
    return time - tmp;
  }

  void restart(){
    time = clock();
  }

  int getCLOCKS_PER_SEC(){
    return CLOCKS_PER_SEC;
  }
};

JNIEXPORT void JNICALL Java_TestJNIArray_addOne___3I( JNIEnv * env, jclass, jintArray intArray) {
  jboolean b;

  Timer timer;
  jint* pint = env->GetIntArrayElements(intArray, &b);//获取指针！！第二个参数可为NULL
  std::string str = b ? "true" : "false";
  long t = timer.getElapsedTimeAndRestart();
  std::cout<<"GetIntArrayElements()耗时: "<< t << "\t为副本？" << str << std::endl;//很悲剧，自己得到的是副本（copy了一份，速度慢啊）
  jsize size = env->GetArrayLength(intArray);

  for (int i = 0; i < size; i++)
    pint[i] += 1;
    env->ReleaseIntArrayElements(intArray, pint, 0);//释放~~~
  //  对于最后一个参数(如果指针指向的数组为副本时，否则该参数不起作用)
  //    0   copy back the content and free the elems buffer
  //    JNI_COMMIT    copy back the content but do not free the elems buffer
  //    JNI_ABORT   free the buffer without copying back the possible changes

  std::cout<<"从c++程序返回~"<<std::endl;


}

JNIEXPORT void JNICALL Java_TestJNIArray_addOne___3D( JNIEnv * env, jclass, jdoubleArray intArray)
{
  jboolean b;
  Timer timer;
  double* pd = (double*)env->GetPrimitiveArrayCritical(intArray, &b);
  //if(pd==NULL)return;理论上应该检查！！！！
  long t = timer.getElapsedTimeAndRestart();
  jsize size = env->GetArrayLength(intArray);
  std::string str = b ? "true" : "false";
  std::cout << "GetPrimitiveArrayCritical()耗时: " << t << "\t为副本？" << str << std::endl;//这次是原始数据了，happy啊！！！

  for(int j = 0;j < 5;j++){ //验证一下，Java中的数据也在更新！！！
    for (int i = 0; i < size; i++){
      pd[i] += 1;
    }
  }
  env->ReleasePrimitiveArrayCritical(intArray, pd, 0);//别忘了释放~~~虽然不知道不释放有什么问题。。。

  std::cout << "从c++程序返回~" << std::endl;
}

JNIEXPORT jintArray JNICALL Java_TestJNIArray_getNewArray( JNIEnv * env, jclass, jint size, jint initValue ) {
  jintArray intArray = env->NewIntArray(size);
  jboolean* pb;
  //jint* pint=env->GetIntArrayElements(intArray,pb);

  jint* pint = new jint[size];

  //std::string ddstr = *pb ? "true" : "false";
  //std::cout<<"自己生成的Java数组，取出指针，为副本？"<<str<<std::endl;

  for (int i=0; i<size; i++) {
    pint[i] = initValue;
  }
  env->ReleaseIntArrayElements(intArray, pint, JNI_COMMIT);
  delete []pint; //如果使用GetIntArrayElements()得到该指针则不可以！！！否则Java直接崩溃了
  return intArray;
}
