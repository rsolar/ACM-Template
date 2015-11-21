
//Miller Rabin大数素数测试
import java.math.BigInteger;

class BigIntegerMillerRabin {
  public final static int Times = 7;

  public static BigInteger powMod(BigInteger a, BigInteger b, BigInteger m) {
    BigInteger ans = BigInteger.ONE;
    a = a.mod(m);
    while (!(b.equals(BigInteger.ZERO))) {
      if ((b.mod(BigInteger.valueOf(2))).equals(BigInteger.ONE)) {
        ans = (ans.multiply(a)).mod(m);
        b = b.subtract(BigInteger.ONE);
      }
      b = b.divide(BigInteger.valueOf(2));
      a = (a.multiply(a)).mod(m);
    }
    return ans;
  }

  public static boolean Miller_Rabin(BigInteger n) {
    if (n.equals(BigInteger.valueOf(2)))
      return true;
    if (n.equals(BigInteger.ONE))
      return false;
    if ((n.mod(BigInteger.valueOf(2))).equals(BigInteger.ZERO))
      return false;
    BigInteger m = n.subtract(BigInteger.ONE);
    BigInteger y = BigInteger.ZERO;
    int k = 0;
    while ((m.mod(BigInteger.valueOf(2))).equals(BigInteger.ZERO)) {
      k++;
      m = m.divide(BigInteger.valueOf(2));
    }
    Random d = new Random();
    for (int i = 0; i < Times; i++) {
      int t = 0;
      if (n.compareTo(BigInteger.valueOf(10000)) == 1) {
        t = 10000;
      } else {
        t = n.intValue() - 1;
      }
      int a = d.nextInt(t) + 1;
      BigInteger x = powMod(BigInteger.valueOf(a), m, n);
      for (int j = 0; j < k; j++) {
        y = (x.multiply(x)).mod(n);
        if (y.equals(BigInteger.ONE) && !(x.equals(BigInteger.ONE))
                && !(x.equals(n.subtract(BigInteger.ONE))))
          return false;
        x = y;
      }
      if (!(y.equals(BigInteger.ONE)))
        return false;
    }
    return true;
  }
}
// pollard rho大数分解
import java.math.BigInteger;
import java.security.SecureRandom;

class PollardRho {
  private final static BigInteger ZERO = new BigInteger("0");
  private final static BigInteger ONE = new BigInteger("1");
  private final static BigInteger TWO = new BigInteger("2");
  private final static SecureRandom random = new SecureRandom();

  public static BigInteger rho(BigInteger N) {
    BigInteger divisor;
    BigInteger c = new BigInteger(N.bitLength(), random);
    BigInteger x = new BigInteger(N.bitLength(), random);
    BigInteger xx = x;
    if (N.mod(TWO).compareTo(ZERO) == 0) {
      return TWO;
    }
    do {
      x = x.multiply(x).mod(N).add(c).mod(N);
      xx = xx.multiply(xx).mod(N).add(c).mod(N);
      xx = xx.multiply(xx).mod(N).add(c).mod(N);
      divisor = x.subtract(xx).gcd(N);
    } while ((divisor.compareTo(ONE)) == 0);
    return divisor;
  }

  public static void factor(BigInteger N) {
    if (N.compareTo(ONE) == 0) {
      return;
    }
    if (N.isProbablePrime(20)) {
      System.out.println(N);
      return;
    }
    BigInteger divisor = rho(N);
    factor(divisor);
    factor(N.divide(divisor));
  }

  public static void main(String[] args) {
    BigInteger N = BigInteger.valueOf(120);
    factor(N);
  }
}
// 反素数 - HDU4392
import java.io.BufferedInputStream;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

class Node {
  private static final int MAXP = 60;
  public BigInteger K;
  public long F;
  public int N;
  public int[] A;

  public Node() {
    K = BigInteger.ZERO;
    A = new int[MAXP];
  }
}

public class Main {
  private static final int MAXIP = 250;
  private static final int MAXP = 60;
  private static BigInteger[] prime;

  private static void init() {
    boolean[] isPrime = new boolean[MAXIP];
    for (int i = 0; i < MAXIP; ++i) {
      isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    for (int i = 4; i < MAXIP; i += 2) {
      isPrime[i] = false;
    }
    for (int i = 3; i < MAXIP; i += 2) {
      for (int j = 3; i * j < MAXIP; j += 2) {
        isPrime[i * j] = false;
      }
    }
    prime = new BigInteger[MAXP];
    for (int i = 0, j = 0; i < MAXIP; ++i) {
      if (isPrime[i]) {
        prime[j++] = BigInteger.valueOf(i);
      }
    }
  }

  public static void main(String args[]) {
    init();
    List<BigInteger> P = new ArrayList<BigInteger>();
    BigInteger MP = BigInteger.ZERO;
    List<Node> ans = new ArrayList<Node>();
    Scanner cin = new Scanner(new BufferedInputStream(System.in));
    while (cin.hasNext()) {
      BigInteger temp = cin.nextBigInteger();
      P.add(temp);
      if (temp.compareTo(MP) == 1) {
        MP = temp;
      }
      ans.add(new Node());
    }
    Map<Long, BigInteger> map = new HashMap<Long, BigInteger>();
    Queue<Node> queue = new LinkedList<Node>();
    Node origin = new Node();
    origin.K = BigInteger.ONE;
    origin.F = 1;
    origin.N = 0;
    queue.add(origin);
    map.put(origin.F, origin.K);
    while (!queue.isEmpty()) {
      Node u = queue.peek();
      queue.remove();
      BigInteger compare = map.get(u.F);
      if (compare != null) {
        if (compare.compareTo(u.K) == -1) {
          continue;
        }
      }
      for (int i = 0; i < P.size(); ++i) {
        if (u.K.compareTo(P.get(i)) <= 0) {
          if (u.F > ans.get(i).F) {
            ans.get(i).F = u.F;
            ans.get(i).K = u.K;
          } else if (u.F == ans.get(i).F) {
            if (u.K.compareTo(ans.get(i).K) == -1) {
              ans.get(i).K = u.K;
            }
          }
        }
      }
      for (int i = 0; i < u.N; ++i) {
        Node v = new Node();
        v.K = u.K.multiply(prime[i]);
        if (v.K.compareTo(MP) <= 0) {
          v.F = u.F / (u.A[i] + 1) * (u.A[i] + 2);
          v.N = u.N;
          for (int j = 0; j < u.N; ++j) {
            v.A[j] = u.A[j];
          }
          ++v.A[i];
          boolean flag = true;
          compare = map.get(v.F);
          if (compare != null) {
            if (compare.compareTo(v.K) <= 0) {
              flag = false;
            } else {
              map.remove(v.F);
            }
          }
          if (flag) {
            queue.add(v);
            map.put(v.F, v.K);
          }
        }
      }
      Node v = new Node();
      v.K = u.K.multiply(prime[u.N]);
      if (v.K.compareTo(MP) <= 0) {
        v.F = u.F * 2;
        v.N = u.N + 1;
        for (int i = 0; i < u.N; ++i) {
          v.A[i] = u.A[i];
        }
        ++v.A[u.N];
        boolean flag = true;
        compare = map.get(v.F);
        if (compare != null) {
          if (compare.compareTo(v.K) <= 0) {
            flag = false;
          } else {
            map.remove(v.F);
          }
        }
        if (flag) {
          queue.add(v);
          map.put(v.F, v.K);
        }
      }
    }
    for (int i = 0; i < ans.size(); ++i) {
      System.out.println(ans.get(i).K.toString() + " " + ans.get(i).F); // 第一个数为满足因子个数最多的K，第二个数为K的因子个数
    }
  }
}
