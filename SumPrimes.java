// PROBLEM  -  The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17. Find the sum of all the primes below two million.
// ALG USED -  Sieve of Eratosthenes
// BIG O    -  O(N log log N)

public class SumPrimes {

    public static void main(String[] args) {
        final int SIZE = 2_000_000;
        boolean[] isPrime = new boolean[SIZE];

        for (int i = 2; i < SIZE; i++) {
            isPrime[i] = true;
        }

        for (int i = 2; i <= (int) Math.sqrt(SIZE); i++) {
            if (isPrime[i]) {
                for (int j = i * i; j < SIZE; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        long sum = 0;
        for (int i = 2; i < SIZE; i++) {
            if (isPrime[i]) {
                sum += i;
            }
        }

        System.out.println(sum);
    }
}
