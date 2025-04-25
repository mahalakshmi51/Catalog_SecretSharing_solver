import java.math.BigInteger;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        // Test Case 1 (n=4, k=3)
        int k1 = 3;
        List<Point> points1 = new ArrayList<>();
        points1.add(new Point(1, "10", "4"));
        points1.add(new Point(2, "2", "111"));
        points1.add(new Point(3, "10", "12"));
        points1.add(new Point(6, "4", "213"));

        // Test Case 2 (n=10, k=7)
        int k2 = 7;
        List<Point> points2 = new ArrayList<>();
        points2.add(new Point(1, "6", "13444211440455345511"));
        points2.add(new Point(2, "15", "aed7015a346d63"));
        points2.add(new Point(3, "15", "6aeeb69631c227c"));
        points2.add(new Point(4, "16", "e1b5e05623d881f"));
        points2.add(new Point(5, "8", "316034514573652620673"));
        points2.add(new Point(6, "3", "2122212201122002221120200210011020220200"));
        points2.add(new Point(7, "3", "20120221122211000100210021102001201112121"));
        points2.add(new Point(8, "6", "20220554335330240002224253"));
        points2.add(new Point(9, "12", "45153788322a1255483"));
        points2.add(new Point(10, "7", "1101613130313526312514143"));

        // Compute secrets
        BigInteger secret1 = computeSecret(points1, k1);
        BigInteger secret2 = computeSecret(points2, k2);

        // Output
        System.out.println("Secret 1: " + secret1);
        System.out.println("Secret 2: " + secret2);
    }

    // Data structure to hold each (x, base, value)
    static class Point {
        int x;
        int base;
        String encodedValue;

        Point(int x, String base, String value) {
            this.x = x;
            this.base = Integer.parseInt(base);
            this.encodedValue = value;
        }

        BigInteger getY() {
            return new BigInteger(encodedValue, base);
        }
    }

    private static BigInteger computeSecret(List<Point> points, int k) {
        List<BigInteger> xValues = new ArrayList<>();
        List<BigInteger> yValues = new ArrayList<>();

        for (int i = 0; i < k; i++) {
            Point p = points.get(i);
            xValues.add(BigInteger.valueOf(p.x));
            yValues.add(p.getY());
        }

        return lagrangeInterpolationAtZero(xValues, yValues);
    }

    private static BigInteger lagrangeInterpolationAtZero(List<BigInteger> x, List<BigInteger> y) {
        BigInteger result = BigInteger.ZERO;

        for (int i = 0; i < x.size(); i++) {
            BigInteger xi = x.get(i);
            BigInteger yi = y.get(i);

            BigInteger num = BigInteger.ONE;
            BigInteger den = BigInteger.ONE;

            for (int j = 0; j < x.size(); j++) {
                if (i == j) continue;
                BigInteger xj = x.get(j);
                num = num.multiply(xj.negate());
                den = den.multiply(xi.subtract(xj));
            }

            BigInteger term = yi.multiply(num).divide(den);
            result = result.add(term);
        }

        return result;
    }
}
