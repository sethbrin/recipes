public class ClassAccess {
  String str = "abcde";
  double number;

  public native void nativeMethod();

  private void javaMethod() {
    System.out.println("call java method succeeded" + number);
  }

  static {
    System.load("/home/zp/work/learning/recipes/jni/classAccess.so");
    //System.loadLibrary("classAccess.so");
  }

  public static void main(String[] args) {
    new ClassAccess().nativeMethod();
  }
}
