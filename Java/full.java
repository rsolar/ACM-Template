import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
  Scanner in;
  PrintWriter out;

  void solve() {
    while (in.hasNext()) {
      int n = in.nextInt();
      int a[] = new int[n + 5];
      for (int i = 0; i < n; i++) {
        a[i] = in.nextInt();
      }

    }
  }

  void run() {
    in = new Scanner(new BufferedInputStream(System.in, 1024));
    out = new PrintWriter(System.out);
    solve();
    out.flush();
  }

  public static void main(String[] args) {
    new Main().run();
  }
}
