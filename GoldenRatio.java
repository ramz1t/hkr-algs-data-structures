import java.util.Scanner;

public class GoldenRatio {

  public static float getGoldenRatio(int n) {
    if (n == 0) return 1;
    return 1 + 1 / getGoldenRatio(n - 1);
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("n: ");
    int n = scanner.nextInt();
    System.out.println("Golden ratio: " + getGoldenRatio(n));
  }

}
