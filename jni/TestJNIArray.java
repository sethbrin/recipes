import java.util.Arrays;

public class TestJNIArray {
  static{
    //System.loadLibrary("TestJNIArray");
    System.load("/home/zp/work/learning/recipes/jni/TestJNIArray.so");
  }

  public static native void addOne(int[] ints);//数组元素+1
  public static native void addOne(double[] ints);//数组元素+1，为了测试，C++中循环了5次
  public static native int[] getNewArray(int size,int initValue);//生成初始值为initValue的数组，数组长度为size

  public static void main(String[] args) throws InterruptedException {
    int n = 20;

    final int[] a = new int[n];

    for (int i = 0; i < a.length; i++) {
      a[i] = i;
    }
    if(n < 50) System.out.println(Arrays.toString(a));
    addOne(a);
    if(n < 50) System.out.println(Arrays.toString(a));

    final double d[] = new double[n];
    for (int i = 0; i < d.length; i++) {
      d[i] = i;
    }
    if(n < 50) System.out.println(Arrays.toString(d));
    addOne(d);
    if(n < 50) System.out.println(Arrays.toString(d));

    //new Thread(new Runnable() {
    //  @Override
    //  public void run() {
    //    addOne(d);
    //  }
    //}).start();
    for (int i = 0; i < 200; i++) {
      Thread.sleep(20);
      //System.out.println(Arrays.toString(d));
      if(d[d.length-1] - d[0] != n - 1) System.out.println("检测到C++端更新数据中");//看看能否找到在C++更新数组时Java端又读取数据的情况
    }

    int[] b = getNewArray(2, 9);
    //System.out.println(Arrays.toString(b));

    int[] c = getNewArray(0, 9);
    //System.out.println(Arrays.toString(c));

  }
}

