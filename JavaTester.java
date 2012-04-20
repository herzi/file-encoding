import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

public class JavaTester {
	private JavaTester () {}

	public static void main (String[] arguments) {
		File folder = new File(".");
		File[] files = folder.listFiles();
		for (int i = 0; i < files.length; i++) {
			if (files[i].getName().indexOf(".txt") < 0) {
				continue;
			}

			try {
				BufferedReader r = new BufferedReader(new FileReader(files[i]));

				System.out.println("(java2)found: " + r.readLine());
			} catch (Exception e) {
				System.err.println("(java2)couldn't read file: '" + files[i].getName());
			}
		}
	}
}
