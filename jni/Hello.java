public class Hello {
  public native void display();
  private native double sumNative(double x, double y);

  public double a;
  public Hello(double a_) {
    this.a = a_;
  }

  public double sum(double x, double y) {
    return sumNative(x, y);
  }

  static {
    System.load("/home/zp/work/learning/recipes/jni/hello.so");
  }

  public static void main(String[] args) {
    new Hello(3.0).display();
    System.out.println(new Hello(4.0).sum(2.0, 3.0));
  }
}
