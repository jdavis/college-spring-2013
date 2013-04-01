import java.util.Scanner;

public class MatrixMultiplier {
	public native void matrix(int arr1[][], int arr2[][], int arr3[][]);

	public static void main(String [] args)
	{
		String dir = System.getProperty("user.dir");
		System.load(dir + "/libmatrix.so");
		Scanner scan = new Scanner(System.in);

		int a[][] = new int[3][3];
		int b[][] = new int[3][3];
		int r[][] = new int[3][3];
	
		/*
		System.out.println("Input is accepted by x x x for each matrix row");
		for(int c = 0; c < 2; c++) {
			System.out.println("Enter the " + (c == 0 ? "first" : "second") + " matrix:");
			for(int i = 0; i < 3; i++) {
				System.out.print("Row " + (i + 1) + ": ");
				String parts[] = scan.nextLine().split("\\s+");
				if (parts.length != 3) {
					System.out.println("Invalid input");
					return;
				}
				for(int j = 0; j < 3; j++) {
					int x = Integer.parseInt(parts[j]);
					if (c == 1) {
						a[i][j] = x;
					} else {
						b[i][j] = x;
					}
				}
			}
		}
		*/
		

		MatrixMultiplier m = new MatrixMultiplier();

		int a2[][] = {
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
		};
		m.matrix(a2, a2, r);
		//m.matrix(a, b, r);

		for(int i = 0; i < r.length; i++) {
			for(int j = 0; j < r[0].length; j++) {
				System.out.print("" + r[i][j] + " ");
			}
			System.out.print("\n");
		}
	}
}
