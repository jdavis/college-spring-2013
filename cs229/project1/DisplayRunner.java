import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.image.BufferedImage;

public class DisplayRunner {
	private JFrame mainWindow;
	CS229 image;

	public static void main(String args[]) {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
					public void run() {
						createAndShowGUI();
					}
				});
	}

	public static void createAndShowGUI() {
		DisplayRunner window = new DisplayRunner();
		window.showWindow();
	}

	public void displayImage() {
		System.out.println("Update image display");
		image.updateUI();
	}

	private void showWindow() {
		image = new CS229(this);

		mainWindow = new JFrame();	
		mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainWindow.setSize(740, 520);
		Container c = mainWindow.getContentPane();
		c.setLayout(new BorderLayout());

		this.setupButtons();
		this.setupImage();

		mainWindow.pack();
		mainWindow.setVisible(true);
	}

	private void setupButtons() {
		JPanel imgButtons = new JPanel();
		JPanel systemButtons = new JPanel();

		JButton openFile = new JButton("Open Image...");
		openFile.setActionCommand("open");
		openFile.addActionListener(image);
		systemButtons.add(openFile);

		JButton rotateL = new JButton("Rotate Left");
		rotateL.setActionCommand("./rotate -90");
		rotateL.addActionListener(image);
		imgButtons.add(rotateL);

		JButton rotateR = new JButton("Rotate Right");
		rotateR.setActionCommand("./rotate 90");
		rotateR.addActionListener(image);
		imgButtons.add(rotateR);

		JButton flipH = new JButton("Horizontal Flip");
		flipH.setActionCommand("./flip h");
		flipH.addActionListener(image);
		imgButtons.add(flipH);

		JButton flipV = new JButton("Vertical Flip");
		flipV.setActionCommand("./flip v");
		flipV.addActionListener(image);
		imgButtons.add(flipV);

		JButton blur = new JButton("Blur/Soften");
		blur.setActionCommand("./convolve smooth.kfile");
		blur.addActionListener(image);
		imgButtons.add(blur);
		
		JButton sharpen = new JButton("Sharpen");
		sharpen.setActionCommand("./convolve sharpen.kfile");
		sharpen.addActionListener(image);
		imgButtons.add(sharpen);

		Container c = mainWindow.getContentPane();
		c.add(systemButtons, BorderLayout.PAGE_START);
		c.add(imgButtons, BorderLayout.PAGE_END);
	}

	private void setupImage() {
		Container c = mainWindow.getContentPane();

		image.setBorder(new EmptyBorder(new Insets(20, 20, 20, 20)));

		c.add(image, BorderLayout.CENTER);
	}
}
