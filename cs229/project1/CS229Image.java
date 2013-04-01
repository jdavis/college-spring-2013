import java.util.*;
import java.io.*;
import java.awt.Color;

public class CS229Image {
	private int width;
	private int height;
	private Color data[][];

	public static void main (String [] args) throws IOException
	{
		System.out.println("Main");
		String fn = "/home/davis/CS229/hw1/etc/mksquare5x5.cs229";

		File f = new File(fn);

		System.out.println(fn + " " + f.length());

		CS229Image i = new CS229Image();
		FileInputStream in = new FileInputStream(f);
		i.read(in);
	}

	public CS229Image() {
		data = new Color[640][480];
	}
	
	public void read(InputStream in) throws IOException {
		byte b[] = new byte[12];

		in.read(b);

		if (b[0] != -1) {
			System.out.println("Make error thing here");
		} else {
			System.out.println("Image is good!");
		}

		for(int f = 0; f < 12; f++)
			System.out.println("F: " + f + " = " + b[f]);

		int rc = (int) b[1] / 8;
		int gc = (int) b[2] / 8;
		int bc = (int) b[3] / 8;
		
		width = bytesToInt(b, 4, 7);
		height = bytesToInt(b, 8, 11);

		if (width != 640 && height != 480) {
			System.out.println("Height and Width not right");
		}

		System.out.println("Width: " + width + " Height: " + height);
		System.out.println("RC: " + rc + " GC: " + gc + " BC: " + bc);
		
		for(int h = 0; h < height; h++) {
			for(int w = 0; w < width; w++) {
				byte R[] = new byte[rc];
				byte G[] = new byte[gc];
				byte B[] = new byte[bc];
				
				in.read(R);
				in.read(G);
				in.read(B);
				
				int red = toColor(R);
				int green = toColor(G);
				int blue = toColor(B);

				System.out.println("Red = " + red + " Green: " + green + " Blue: " + blue);
				data[h][w] = new Color(red, green, blue);
			}
		}
	}

	public int bytesToInt(byte b[], int s, int e) {
		int x = 0;
		for(int f = s; f <= e; f++) {
			System.out.println("Byte " + f + " " + b[f]);
			x <<= 8;
			x |= b[f];
		}

		return x == -1 ? 255 : x;
	}

	public int toColor(byte b[]) {
		int x = bytesToInt(b, 0, b.length - 1);
		if (b.length == 2) {
			x = x / 257;
		}
		return x;
	}
}
