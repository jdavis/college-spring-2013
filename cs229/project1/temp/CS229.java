import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.event.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.JFileChooser;
import java.awt.Graphics;

public class CS229 extends JPanel implements ActionListener {
	private DisplayRunner callback;
	private BufferedImage image;

	private long width;
	private long height;
	private Pixel data[][];

	public CS229(DisplayRunner cb) {
		data = new Pixel[640][480];
		callback = cb;
		this.setPreferredSize(new Dimension(640, 640));
	}

@Override
    public void paintComponent(Graphics g) {
		System.out.println("Painting");
		g.clearRect(0, 0, 640, 640);
		g.drawImage(image, 0, 0, new Color(Color.TRANSLUCENT, true), null);
	}

	public void openFile() {
		System.out.println("Opening file..");
		String dir = System.getProperty("user.dir");
		JFileChooser chooser = new JFileChooser(dir + "/../etc");
		int fileReturn = chooser.showOpenDialog(null);
		File file;

		if (fileReturn == JFileChooser.APPROVE_OPTION) {
			try {
				file = chooser.getSelectedFile();
				System.out.println("Chose: " + file.getName());
				FileInputStream in = new FileInputStream(file);
				read(in);
			} catch(Exception e) {
				System.out.println("Exception");
				System.out.println(e);
				error("Could not read image");
			}
		}
	}

	public void error(String message) {
		JOptionPane.showMessageDialog(null, message);
	}

	public void write(OutputStream out) throws IOException {
		System.out.println("Writing image");
		out.write(255);
		out.write(16);
		out.write(16);
		out.write(16);

		out.write(intToBytes(width));
		out.write(intToBytes(height));

		for(int h = 0; h < height; h++) {
			for(int w = 0; w < width; w++) {
				Pixel p = data[h][w];
				//Color c = p.color;
				//System.out.println(c);
				//out.write(c.getRed());
				//out.write(c.getGreen());
				//out.write(c.getBlue());
				//out.write(p.colorBytes());
				p.writePixel(out);
			}
		}

		out.close();
	}

	public void read(InputStream in) throws IOException {
		System.out.println("Reading InputSTream for CS229 image\n");
		image = new BufferedImage(640, 640, BufferedImage.TYPE_INT_ARGB);
		byte b[] = new byte[12];

		in.read(b);

		if (b[0] != -1) {
			error("Image not supported");
			return;
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

		if (width > 640 || height > 480) {
			error("The image is too big! Only 640x480 and smaller!");
			return;
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

				Pixel p = new Pixel(red, green, blue, rc, gc, bc);
				//System.out.println(p.color);
				data[h][w] = p;
				image.setRGB(w, h, p.color.getRGB());
			}
		}

		in.close();
	}

	public void runProgram(String prog) {
		String dir = System.getProperty("user.dir");
		File f = new File(dir);
		try {
			Process p = Runtime.getRuntime().exec(prog, null, f);
			OutputStream out = p.getOutputStream();
			InputStream in = p.getInputStream();

			System.out.println("Running program and now writing image");
			write(out);
			read(in);
		} catch (IOException e) {
			error("Error occured while running operation");
			return;
		}
	}

	public void actionPerformed(ActionEvent e) {
		String c = e.getActionCommand();

		if (c.startsWith("./flip")) {
			this.runProgram(c);
		} else if (c.startsWith("./rotate")) {
			this.runProgram(c);
		} else if (c.startsWith("./convolve")) {
			this.runProgram(c);
		} else if (c.equals("open")) {
			this.openFile();
		}

		callback.displayImage();
	} 

	public long bytesToInt(byte b[], int s, int e) {
		long x = 0;
		for(int f = s; f <= e; f++) {
			x <<= 8;
			x |= b[f] & 0xFF;
		}

		return x == -1 ? 255 : x;
	}

	public byte[] intToBytes(long i) {
		byte b[] = new byte[4];
		for(int f = 3; f > 0; f--) {
			b[f] = (byte) i;
			i >>= 8;
		}

		return b;
	}

	public int toColor(byte b[]) {
		long x = bytesToInt(b, 0, b.length - 1);
		return (int) x;
	}

	private class Pixel {
		int r, g, b;
		Color color;
		public Pixel(int r, int g, int b, int rc, int gc, int bc) {
			this.r = r * (rc == 1 ? 257 : 1);
			this.g = g * (gc == 1 ? 257 : 1);
			this.b = b * (bc == 1 ? 257 : 1);

			r /= (rc == 2 ? 257 : 1);
			g /= (gc == 2 ? 257 : 1);
			b /= (bc == 2 ? 257 : 1);

			color = new Color(r, g, b);
		}

		public void writePixel(OutputStream out) throws IOException {
			out.write(r >> 8);
			out.write(r);
			out.write(g >> 8);
			out.write(g);
			out.write(b >> 8);
			out.write(b);
		}
	}
}
