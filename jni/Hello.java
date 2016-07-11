public class Hello {
  public native void display();
  private native double sumNative(double x, double y);

  public double sum(double x, double y) {
    return sumNative(x, y);
  }

  static {
    System.load("/home/zp/work/learning/recipes/jni/hello.so");
  }

  public static void main(String[] args) {
    new Hello().display();
    System.out.println(new Hello().sum(2.0, 3.0));
  }
}
