import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
  Scanner sc;
  PrintWriter out;

  void solve() {
    while (sc.hasNext()) {
      int n = sc.nextInt();
      int a[] = new int[n + 5];
      for (int i = 0; i < n; i++) {
        a[i] = sc.nextInt();
      }

    }
  }

  void run() {
    sc = new Scanner(new BufferedInputStream(System.in));
    out = new PrintWriter(System.out);
    solve();
    out.flush();
  }

  public static void main(String[] args) {
    new Main().run();
  }
}
